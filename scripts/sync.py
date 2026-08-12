#!/usr/bin/env python3
"""
LeetCode → GitHub Daily Sync Script
=====================================
Fetches RECENT accepted submissions from LeetCode and updates
the problems/ directory. Designed to be run by GitHub Actions daily.

This script checks the last-modified timestamps of existing solution files
to avoid redundant writes, and only commits when there are actual changes.

ENVIRONMENT VARIABLES:
    LEETCODE_SESSION   - Your LeetCode session cookie (GitHub Secret)
    PROBLEMS_DIR       - Output directory (default: problems/)
"""

import os
import re
import sys
import time
import html
import logging
from pathlib import Path
from typing import Optional

import requests
from dotenv import load_dotenv

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------

load_dotenv()

LEETCODE_SESSION  = os.getenv("LEETCODE_SESSION", "")
PROBLEMS_DIR      = Path(os.getenv("PROBLEMS_DIR", "problems"))
LEETCODE_BASE_URL = "https://leetcode.com"
GRAPHQL_URL       = f"{LEETCODE_BASE_URL}/graphql"

REQUEST_DELAY_S   = 1.5
# How many pages to look back (PAGE_SIZE=20 each) when checking for new problems
LOOKBACK_PAGES    = 5
PAGE_SIZE         = 20

LANG_EXT = {
    "cpp":           "cpp",
    "c++":           "cpp",
    "python":        "py",
    "python3":       "py",
    "mysql":         "sql",
    "ms sql server": "sql",
    "oraclesql":     "sql",
    "java":          "java",
    "javascript":    "js",
    "typescript":    "ts",
    "golang":        "go",
    "rust":          "rs",
    "swift":         "swift",
    "kotlin":        "kt",
    "scala":         "scala",
    "ruby":          "rb",
    "php":           "php",
    "bash":          "sh",
}

# ---------------------------------------------------------------------------
# Logging
# ---------------------------------------------------------------------------

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%H:%M:%S",
)
log = logging.getLogger(__name__)

# ---------------------------------------------------------------------------
# GraphQL queries
# ---------------------------------------------------------------------------

SUBMISSIONS_QUERY = """
query submissionList($offset: Int!, $limit: Int!, $lastKey: String) {
  submissionList(offset: $offset, limit: $limit, lastKey: $lastKey) {
    lastKey
    hasNext
    submissions {
      id
      title
      titleSlug
      status
      statusDisplay
      lang
      timestamp
      url
      isPending
    }
  }
}
"""

SUBMISSION_DETAIL_QUERY = """
query submissionDetails($submissionId: Int!) {
  submissionDetails(submissionId: $submissionId) {
    runtime
    runtimeDisplay
    memory
    memoryDisplay
    code
    lang {
      name
      verboseName
    }
  }
}
"""

PROBLEM_DETAIL_QUERY = """
query questionData($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    questionId
    questionFrontendId
    title
    titleSlug
    difficulty
    content
    topicTags { name }
    hints
  }
}
"""

# ---------------------------------------------------------------------------
# Session
# ---------------------------------------------------------------------------

def build_session() -> requests.Session:
    if not LEETCODE_SESSION:
        log.error("LEETCODE_SESSION is not set.")
        sys.exit(1)
    session = requests.Session()
    session.cookies.set("LEETCODE_SESSION", LEETCODE_SESSION, domain="leetcode.com")
    session.headers.update({
        "User-Agent": (
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
            "AppleWebKit/537.36 Chrome/120.0.0.0 Safari/537.36"
        ),
        "Referer": LEETCODE_BASE_URL,
    })
    # Fetch CSRF token
    try:
        resp = session.get(LEETCODE_BASE_URL, timeout=10)
        csrf = resp.cookies.get("csrftoken", "")
        if csrf:
            session.headers["x-csrftoken"] = csrf
    except Exception:
        pass
    return session


def graphql(session: requests.Session, query: str, variables: dict) -> dict:
    resp = session.post(GRAPHQL_URL, json={"query": query, "variables": variables}, timeout=30)
    resp.raise_for_status()
    return resp.json()

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def html_to_text(html_str: str) -> str:
    if not html_str:
        return ""
    text = html.unescape(html_str)
    text = re.sub(r"<strong>(.*?)</strong>", r"**\1**", text, flags=re.DOTALL)
    text = re.sub(r"<em>(.*?)</em>",         r"*\1*",   text, flags=re.DOTALL)
    text = re.sub(r"<code>(.*?)</code>",     r"`\1`",   text, flags=re.DOTALL)
    text = re.sub(r"<pre>(.*?)</pre>",       r"```\n\1\n```", text, flags=re.DOTALL)
    text = re.sub(r"<li>(.*?)</li>",         r"- \1",   text, flags=re.DOTALL)
    text = re.sub(r"</?ul>|</?ol>",          "",        text)
    text = re.sub(r"<p>(.*?)</p>",           r"\1\n",   text, flags=re.DOTALL)
    text = re.sub(r"<br\s*/?>",             "\n",      text)
    text = re.sub(r"<[^>]+>",              "",        text)
    text = re.sub(r"\n{3,}",              "\n\n",    text)
    return text.strip()


def slugify(title: str) -> str:
    return re.sub(r"[^a-z0-9]+", "-", title.lower()).strip("-")


def folder_name(frontend_id: str, title: str) -> str:
    return f"{str(frontend_id).zfill(4)}-{slugify(title)}"


def file_ext(lang: str) -> str:
    return LANG_EXT.get(lang.lower(), lang.lower())


def existing_problems() -> set[str]:
    """Return set of problem slugs already stored locally."""
    slugs = set()
    if not PROBLEMS_DIR.exists():
        return slugs
    for folder in PROBLEMS_DIR.iterdir():
        if folder.is_dir():
            # folder name pattern: NNNN-problem-slug
            # We track by folder stem to detect existing entries
            slugs.add(folder.name)
    return slugs


# ---------------------------------------------------------------------------
# File generation
# ---------------------------------------------------------------------------

def build_readme(problem: dict, lang: str, runtime: str = "", memory: str = "") -> str:
    fid   = problem.get("questionFrontendId", "?")
    title = problem.get("title", "Unknown")
    diff  = problem.get("difficulty", "Unknown")
    slug  = problem.get("titleSlug", "")
    body  = html_to_text(problem.get("content", ""))
    tags  = ", ".join(t["name"] for t in problem.get("topicTags", []))
    hints = problem.get("hints", [])

    perf = ""
    if runtime:
        perf += f"- **Runtime:** {runtime}\n"
    if memory:
        perf += f"- **Memory:** {memory}\n"

    hints_section = ""
    if hints:
        hints_md = "\n".join(f"{i+1}. {html_to_text(h)}" for i, h in enumerate(hints))
        hints_section = f"\n## 💡 Hints\n\n{hints_md}\n"

    return f"""# {fid}. {title}

**Difficulty:** {diff} | **Language:** {lang.upper()} | **Tags:** {tags or 'N/A'}

🔗 [View on LeetCode](https://leetcode.com/problems/{slug}/)

---

## 📝 Problem Statement

{body}

---

## 🚀 My Solution

- **Language:** {lang.upper()}
{perf}
{hints_section}
---

*Auto-synced by [DSA-Progress](https://github.com/AnubhavKiroula/DSA-Progress)*
"""


def write_problem(problem: dict, code: str, lang: str,
                  runtime: str = "", memory: str = "") -> bool:
    """Write problem folder. Returns True if any file was created/updated."""
    fid   = problem.get("questionFrontendId", "0")
    title = problem.get("title", "unknown")
    fname = folder_name(fid, title)
    fpath = PROBLEMS_DIR / fname
    fpath.mkdir(parents=True, exist_ok=True)

    ext      = file_ext(lang)
    sol_name = f"{fname}.{ext}"
    changed  = False

    readme_path = fpath / "README.md"
    readme_text = build_readme(problem, lang, runtime, memory)
    if not readme_path.exists() or readme_path.read_text(encoding="utf-8") != readme_text:
        readme_path.write_text(readme_text, encoding="utf-8")
        changed = True

    sol_path = fpath / sol_name
    if not sol_path.exists() or sol_path.read_text(encoding="utf-8") != code:
        # Remove files with different extensions (language changed)
        for old in fpath.iterdir():
            if old.name != "README.md" and old.suffix != f".{ext}":
                old.unlink()
        sol_path.write_text(code, encoding="utf-8")
        changed = True

    if changed:
        log.info("  ✅  Updated: problems/%s/", fname)
    return changed


# ---------------------------------------------------------------------------
# Sync logic
# ---------------------------------------------------------------------------

def fetch_recent_accepted(session: requests.Session) -> dict[str, dict]:
    """Fetch the last LOOKBACK_PAGES pages of submissions, keep latest accepted per slug."""
    accepted: dict[str, dict] = {}
    offset   = 0
    last_key = None

    for page in range(1, LOOKBACK_PAGES + 1):
        log.info("  Fetching submissions page %d/%d…", page, LOOKBACK_PAGES)
        data = graphql(session, SUBMISSIONS_QUERY, {
            "offset": offset, "limit": PAGE_SIZE, "lastKey": last_key
        })
        sl   = data.get("data", {}).get("submissionList", {})
        subs = sl.get("submissions", [])

        for sub in subs:
            if sub.get("statusDisplay") != "Accepted":
                continue
            slug = sub["titleSlug"]
            ts   = int(sub.get("timestamp", 0))
            if slug not in accepted or ts > int(accepted[slug].get("timestamp", 0)):
                sub["timestamp"] = ts   # normalise to int
                accepted[slug] = sub

        if not sl.get("hasNext"):
            break
        last_key  = sl.get("lastKey")
        offset   += PAGE_SIZE
        time.sleep(REQUEST_DELAY_S)

    return accepted


def build_commit_message(updated: list[dict]) -> str:
    """
    Build a LeetHub-style commit message.

    Single problem:
        Time: 56 ms (96.46%), Space: 59 MB (33.52%) - AutoSync
        \n
        0011. Container With Most Water

    Multiple problems:
        AutoSync: 3 new LeetCode solution(s) [2026-08-12]
        \n
        - 0011. Container With Most Water | Time: 56ms, Space: 59MB
        - 0001. Two Sum                   | Time: 0ms, Space: 8MB
        ...
    """
    import datetime
    today = datetime.date.today().isoformat()

    if len(updated) == 1:
        p = updated[0]
        runtime = p.get("runtime", "N/A")
        memory  = p.get("memory",  "N/A")
        fid     = str(p.get("questionFrontendId", "?")).zfill(4)
        title   = p.get("title", "Unknown")
        return (
            f"Time: {runtime}, Space: {memory} - AutoSync\n\n"
            f"{fid}. {title}"
        )
    else:
        lines = [f"AutoSync: {len(updated)} new LeetCode solution(s) [{today}]", ""]
        for p in updated:
            fid     = str(p.get("questionFrontendId", "?")).zfill(4)
            title   = p.get("title", "Unknown")
            runtime = p.get("runtime", "N/A")
            memory  = p.get("memory",  "N/A")
            lines.append(f"- {fid}. {title} | Time: {runtime}, Space: {memory}")
        return "\n".join(lines)


def main():
    session = build_session()
    PROBLEMS_DIR.mkdir(parents=True, exist_ok=True)

    log.info("🔍 Fetching recent accepted submissions…")
    accepted = fetch_recent_accepted(session)
    log.info("Found %d unique accepted problems in lookback window.", len(accepted))

    any_changes = False
    counts: dict[str, int] = {}
    updated_problems: list[dict] = []   # track per-problem stats for commit msg

    # Count existing solutions
    for folder in PROBLEMS_DIR.iterdir():
        if not folder.is_dir():
            continue
        for f in folder.iterdir():
            if f.name != "README.md":
                ext = f.suffix.lstrip(".")
                counts[ext] = counts.get(ext, 0) + 1

    for slug, sub in accepted.items():
        sub_id = sub["id"]
        lang   = sub.get("lang", "unknown")
        title  = sub.get("title", slug)
        log.info("Processing: %s (%s)", title, lang)

        # Fetch code + performance stats
        time.sleep(REQUEST_DELAY_S)
        try:
            detail  = graphql(session, SUBMISSION_DETAIL_QUERY, {"submissionId": int(sub_id)})
            d       = detail.get("data", {}).get("submissionDetails", {})
            code    = d.get("code", "")
            runtime = d.get("runtimeDisplay", "N/A")
            memory  = d.get("memoryDisplay",  "N/A")
        except Exception as exc:
            log.warning("  Could not fetch details for %s: %s", slug, exc)
            continue

        if not code:
            continue

        # Fetch problem metadata
        time.sleep(REQUEST_DELAY_S)
        try:
            prob_data = graphql(session, PROBLEM_DETAIL_QUERY, {"titleSlug": slug})
            problem   = prob_data.get("data", {}).get("question") or {
                "questionFrontendId": sub_id,
                "title":     title,
                "titleSlug": slug,
                "difficulty": "Unknown",
                "content":   "",
                "topicTags": [],
                "hints":     [],
            }
        except Exception:
            problem = {
                "questionFrontendId": sub_id,
                "title":     title,
                "titleSlug": slug,
                "difficulty": "Unknown",
                "content":   "",
                "topicTags": [],
                "hints":     [],
            }

        changed = write_problem(problem, code, lang, runtime, memory)
        if changed:
            any_changes = True
            ext = file_ext(lang)
            counts[ext] = counts.get(ext, 0) + 1
            # Store stats for commit message
            updated_problems.append({
                "questionFrontendId": problem.get("questionFrontendId", sub_id),
                "title":   problem.get("title", title),
                "runtime": runtime,
                "memory":  memory,
            })

    # Update root README stats
    if any_changes:
        update_readme_stats(counts)
        log.info("✅ Sync complete — changes detected.")
    else:
        log.info("✅ Sync complete — no new changes.")

    # Signal to GitHub Actions: changes flag + LeetHub-style commit message
    if "GITHUB_OUTPUT" in os.environ:
        commit_msg = build_commit_message(updated_problems) if updated_problems else ""
        # Escape newlines for GITHUB_OUTPUT multiline support
        with open(os.environ["GITHUB_OUTPUT"], "a") as fh:
            fh.write(f"changes={'true' if any_changes else 'false'}\n")
            if commit_msg:
                # Use heredoc syntax for multiline values
                fh.write("commit_msg<<EOF\n")
                fh.write(commit_msg + "\n")
                fh.write("EOF\n")


def update_readme_stats(counts: dict[str, int]) -> None:
    root_readme = Path("README.md")
    if not root_readme.exists():
        return
    text  = root_readme.read_text(encoding="utf-8")
    total = sum(counts.values())

    def replace_row(t, metric, value):
        pattern = rf"(\|\s*{re.escape(metric)}\s*\|\s*)(\d+)(\s*\|)"
        return re.sub(pattern, rf"\g<1>{value}\3", t)

    text = replace_row(text, "Total Problems Solved", total)
    text = replace_row(text, "C++ Solutions",         counts.get("cpp", 0))
    text = replace_row(text, "Python Solutions",      counts.get("py", 0))
    text = replace_row(text, "SQL Solutions",         counts.get("sql", 0))
    root_readme.write_text(text, encoding="utf-8")
    log.info("📊 Updated stats in README.md")


if __name__ == "__main__":
    main()
