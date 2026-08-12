#!/usr/bin/env python3
"""
LeetCode → GitHub One-Time Backfill Script
==========================================
Fetches ALL your past accepted submissions from LeetCode and creates
structured problem folders with README.md and solution files.

USAGE:
    pip install requests python-dotenv
    cp scripts/.env.example .env   # then fill in your values
    python scripts/backfill.py

ENVIRONMENT VARIABLES (in .env or exported):
    LEETCODE_SESSION   - Your LeetCode session cookie
    LEETCODE_USERNAME  - Your LeetCode username (public profile)
    PROBLEMS_DIR       - Output directory (default: problems/)
"""

import os
import re
import sys
import time
import json
import html
import logging
import argparse
from pathlib import Path
from typing import Optional

import requests
from dotenv import load_dotenv

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------

load_dotenv()

LEETCODE_SESSION  = os.getenv("LEETCODE_SESSION", "")
LEETCODE_USERNAME = os.getenv("LEETCODE_USERNAME", "AnubhavKiroula")
PROBLEMS_DIR      = Path(os.getenv("PROBLEMS_DIR", "problems"))
LEETCODE_BASE_URL = "https://leetcode.com"
GRAPHQL_URL       = f"{LEETCODE_BASE_URL}/graphql"
SUBMISSIONS_URL   = f"{LEETCODE_BASE_URL}/api/submissions/"

# Rate-limiting: be polite to LeetCode's servers
REQUEST_DELAY_S   = 1.5   # seconds between API calls
PAGE_SIZE         = 20    # submissions per page (max 20)

# Supported language → file extension mapping
LANG_EXT = {
    "cpp":        "cpp",
    "c++":        "cpp",
    "python":     "py",
    "python3":    "py",
    "mysql":      "sql",
    "ms sql server": "sql",
    "oraclesql":  "sql",
    "java":       "java",
    "javascript": "js",
    "typescript": "ts",
    "golang":     "go",
    "rust":       "rs",
    "swift":      "swift",
    "kotlin":     "kt",
    "scala":      "scala",
    "ruby":       "rb",
    "php":        "php",
    "bash":       "sh",
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
# LeetCode API helpers
# ---------------------------------------------------------------------------

def build_session() -> requests.Session:
    """Build a requests.Session pre-loaded with the LeetCode auth cookie."""
    if not LEETCODE_SESSION:
        log.error(
            "LEETCODE_SESSION is not set. "
            "Set it in .env or export it as an environment variable."
        )
        sys.exit(1)

    session = requests.Session()
    session.cookies.set("LEETCODE_SESSION", LEETCODE_SESSION, domain="leetcode.com")
    session.headers.update({
        "User-Agent": (
            "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
            "AppleWebKit/537.36 (KHTML, like Gecko) "
            "Chrome/120.0.0.0 Safari/537.36"
        ),
        "Referer": LEETCODE_BASE_URL,
        "x-csrftoken": get_csrf_token(session),
    })
    return session


def get_csrf_token(session: requests.Session) -> str:
    """Fetch the CSRF token required for GraphQL POST requests."""
    try:
        resp = session.get(LEETCODE_BASE_URL, timeout=10)
        token = resp.cookies.get("csrftoken", "")
        if not token:
            # Try from cookie jar
            for cookie in session.cookies:
                if cookie.name == "csrftoken":
                    return cookie.value
        return token
    except requests.RequestException as exc:
        log.warning("Could not fetch CSRF token: %s", exc)
        return ""


def graphql_query(session: requests.Session, query: str, variables: dict) -> dict:
    """Execute a GraphQL query and return the JSON response."""
    payload = {"query": query, "variables": variables}
    resp = session.post(GRAPHQL_URL, json=payload, timeout=30)
    resp.raise_for_status()
    return resp.json()


# ---------------------------------------------------------------------------
# Fetch submissions (paginated)
# ---------------------------------------------------------------------------

SUBMISSIONS_QUERY = """
query submissionList($offset: Int!, $limit: Int!, $lastKey: String, $questionSlug: String) {
  submissionList(
    offset: $offset
    limit: $limit
    lastKey: $lastKey
    questionSlug: $questionSlug
  ) {
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
    question {
      title
      titleSlug
      questionId
      difficulty
      content
      exampleTestcases
      topicTags {
        name
      }
      constraints: metaData
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
    exampleTestcases
    topicTags {
      name
    }
    hints
    sampleTestCase
  }
}
"""


def fetch_all_accepted_submissions(session: requests.Session) -> dict[str, dict]:
    """
    Fetch all accepted submissions, keeping only the LATEST per problem slug.
    Returns: { titleSlug -> submission_dict }
    """
    accepted: dict[str, dict] = {}
    offset = 0
    last_key = None
    page = 1

    log.info("Fetching submissions for user: %s", LEETCODE_USERNAME)

    while True:
        log.info("  Page %d (offset=%d)…", page, offset)
        variables = {
            "offset": offset,
            "limit": PAGE_SIZE,
            "lastKey": last_key,
        }
        try:
            data = graphql_query(session, SUBMISSIONS_QUERY, variables)
            sl = data.get("data", {}).get("submissionList", {})
        except Exception as exc:
            log.error("Failed to fetch page %d: %s", page, exc)
            break

        submissions = sl.get("submissions", [])
        for sub in submissions:
            if sub.get("statusDisplay") != "Accepted":
                continue
            slug = sub.get("titleSlug", "")
            ts   = int(sub.get("timestamp", 0))
            # Keep only the most recent accepted submission per problem
            if slug not in accepted or ts > int(accepted[slug].get("timestamp", 0)):
                sub["timestamp"] = ts   # normalise to int
                accepted[slug] = sub

        has_next = sl.get("hasNext", False)
        last_key = sl.get("lastKey")

        if not has_next:
            log.info("All pages fetched. Found %d unique accepted problems.", len(accepted))
            break

        offset += PAGE_SIZE
        page   += 1
        time.sleep(REQUEST_DELAY_S)

    return accepted


def fetch_submission_code(session: requests.Session, submission_id: str) -> Optional[str]:
    """Fetch the actual code for a submission ID."""
    try:
        data = graphql_query(
            session, SUBMISSION_DETAIL_QUERY,
            {"submissionId": int(submission_id)}
        )
        details = data.get("data", {}).get("submissionDetails", {})
        return details.get("code")
    except Exception as exc:
        log.warning("Could not fetch code for submission %s: %s", submission_id, exc)
        return None


def fetch_problem_details(session: requests.Session, title_slug: str) -> Optional[dict]:
    """Fetch full problem metadata (content, constraints, examples)."""
    try:
        time.sleep(REQUEST_DELAY_S)
        data = graphql_query(session, PROBLEM_DETAIL_QUERY, {"titleSlug": title_slug})
        return data.get("data", {}).get("question")
    except Exception as exc:
        log.warning("Could not fetch details for %s: %s", title_slug, exc)
        return None


# ---------------------------------------------------------------------------
# HTML → plain text
# ---------------------------------------------------------------------------

def html_to_text(html_str: str) -> str:
    """Very lightweight HTML → Markdown converter."""
    if not html_str:
        return ""
    # Unescape HTML entities
    text = html.unescape(html_str)
    # Tags → readable equivalents
    text = re.sub(r"<strong>(.*?)</strong>", r"**\1**", text, flags=re.DOTALL)
    text = re.sub(r"<em>(.*?)</em>",       r"*\1*",   text, flags=re.DOTALL)
    text = re.sub(r"<code>(.*?)</code>",   r"`\1`",   text, flags=re.DOTALL)
    text = re.sub(r"<pre>(.*?)</pre>",     r"```\n\1\n```", text, flags=re.DOTALL)
    text = re.sub(r"<li>(.*?)</li>",       r"- \1",   text, flags=re.DOTALL)
    text = re.sub(r"</?ul>|</?ol>",        "",        text)
    text = re.sub(r"<p>(.*?)</p>",         r"\1\n",   text, flags=re.DOTALL)
    text = re.sub(r"<br\s*/?>",            "\n",      text)
    # Strip remaining tags
    text = re.sub(r"<[^>]+>", "", text)
    # Collapse excessive blank lines
    text = re.sub(r"\n{3,}", "\n\n", text)
    return text.strip()


# ---------------------------------------------------------------------------
# File generation
# ---------------------------------------------------------------------------

def slugify(title: str) -> str:
    """Convert a problem title to a folder-friendly slug."""
    slug = title.lower()
    slug = re.sub(r"[^a-z0-9]+", "-", slug)
    slug = slug.strip("-")
    return slug


def get_folder_name(frontend_id: str, title: str) -> str:
    """Return the canonical folder name: e.g. 0001-two-sum"""
    num = str(frontend_id).zfill(4)
    return f"{num}-{slugify(title)}"


def get_file_ext(lang: str) -> str:
    """Map LeetCode language name to file extension."""
    return LANG_EXT.get(lang.lower(), lang.lower())


def build_readme(problem: dict, lang: str, runtime: str = "", memory: str = "") -> str:
    """Generate the per-problem README.md content."""
    frontend_id = problem.get("questionFrontendId", "?")
    title       = problem.get("title", "Unknown")
    difficulty  = problem.get("difficulty", "Unknown")
    slug        = problem.get("titleSlug", "")
    content     = html_to_text(problem.get("content", ""))
    tags        = ", ".join(t["name"] for t in problem.get("topicTags", []))
    hints       = problem.get("hints", [])

    perf_lines = ""
    if runtime:
        perf_lines += f"- **Runtime:** {runtime}\n"
    if memory:
        perf_lines += f"- **Memory:** {memory}\n"

    hints_section = ""
    if hints:
        hints_md = "\n".join(f"{i+1}. {html_to_text(h)}" for i, h in enumerate(hints))
        hints_section = f"\n## 💡 Hints\n\n{hints_md}\n"

    return f"""# {frontend_id}. {title}

**Difficulty:** {difficulty} | **Language:** {lang.upper()} | **Tags:** {tags or 'N/A'}

🔗 [View on LeetCode](https://leetcode.com/problems/{slug}/)

---

## 📝 Problem Statement

{content}

---

## 🚀 My Solution

- **Language:** {lang.upper()}
{perf_lines}
{hints_section}
---

*Auto-synced by [DSA-Progress](https://github.com/AnubhavKiroula/DSA-Progress)*
"""


def write_problem(
    base_dir: Path,
    problem: dict,
    code: str,
    lang: str,
    runtime: str = "",
    memory: str = "",
) -> None:
    """Create/update the folder + README.md + solution file for one problem."""
    frontend_id = problem.get("questionFrontendId", "0")
    title       = problem.get("title", "unknown")
    folder_name = get_folder_name(frontend_id, title)
    folder_path = base_dir / folder_name
    folder_path.mkdir(parents=True, exist_ok=True)

    ext      = get_file_ext(lang)
    sol_name = f"{folder_name}.{ext}"

    # Write README
    readme_path = folder_path / "README.md"
    readme_path.write_text(
        build_readme(problem, lang, runtime, memory),
        encoding="utf-8"
    )

    # Remove stale solution files (different language from a previous run)
    for old_file in folder_path.iterdir():
        if old_file.name != "README.md" and old_file.suffix != f".{ext}":
            old_file.unlink()
            log.debug("  Removed stale file: %s", old_file.name)

    # Write solution
    sol_path = folder_path / sol_name
    sol_path.write_text(code, encoding="utf-8")

    log.info("  ✅  %s  →  problems/%s/", title, folder_name)


# ---------------------------------------------------------------------------
# Stats updater
# ---------------------------------------------------------------------------

def update_readme_stats(base_dir: Path, counts: dict[str, int]) -> None:
    """Patch the Stats table in the root README.md."""
    root_readme = base_dir.parent / "README.md"
    if not root_readme.exists():
        return

    text = root_readme.read_text(encoding="utf-8")
    total = sum(counts.values())

    def replace_row(text, metric, value):
        pattern = rf"(\|\s*{re.escape(metric)}\s*\|\s*)(\d+)(\s*\|)"
        return re.sub(pattern, rf"\g<1>{value}\3", text)

    text = replace_row(text, "Total Problems Solved", total)
    text = replace_row(text, "C++ Solutions",         counts.get("cpp", 0))
    text = replace_row(text, "Python Solutions",      counts.get("py", 0))
    text = replace_row(text, "SQL Solutions",         counts.get("sql", 0))

    root_readme.write_text(text, encoding="utf-8")
    log.info("📊 Updated root README stats: %d total problems.", total)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def parse_args():
    parser = argparse.ArgumentParser(
        description="Backfill all LeetCode accepted submissions into structured folders."
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Fetch and print info but do not write any files.",
    )
    parser.add_argument(
        "--limit",
        type=int,
        default=0,
        help="Stop after processing N problems (0 = all). Useful for testing.",
    )
    return parser.parse_args()


def main():
    args = parse_args()
    session = build_session()

    # 1. Fetch all latest accepted submissions
    accepted = fetch_all_accepted_submissions(session)
    if not accepted:
        log.warning("No accepted submissions found. Check your LEETCODE_SESSION cookie.")
        sys.exit(0)

    PROBLEMS_DIR.mkdir(parents=True, exist_ok=True)
    log.info("Writing problems to: %s", PROBLEMS_DIR.resolve())

    counts: dict[str, int] = {}
    processed = 0

    for slug, sub in accepted.items():
        if args.limit and processed >= args.limit:
            log.info("--limit %d reached, stopping.", args.limit)
            break

        sub_id = sub.get("id")
        lang   = sub.get("lang", "unknown")
        title  = sub.get("title", slug)
        log.info("[%d/%d] %s (%s)…", processed + 1, len(accepted), title, lang)

        # 2. Fetch submission code
        time.sleep(REQUEST_DELAY_S)
        code = fetch_submission_code(session, sub_id)
        if not code:
            log.warning("  Skipping %s — could not fetch code.", slug)
            continue

        # 3. Fetch full problem metadata
        problem = fetch_problem_details(session, slug)
        if not problem:
            # Minimal fallback so we still save the code
            problem = {
                "questionFrontendId": sub.get("id", "0000"),
                "title":      title,
                "titleSlug":  slug,
                "difficulty": "Unknown",
                "content":    "",
                "topicTags":  [],
                "hints":      [],
            }

        ext = get_file_ext(lang)
        counts[ext] = counts.get(ext, 0) + 1

        if args.dry_run:
            log.info("  [DRY RUN] Would write problems/%s/", get_folder_name(
                problem.get("questionFrontendId", "0"), title
            ))
        else:
            write_problem(PROBLEMS_DIR, problem, code, lang)

        processed += 1

    log.info("Done! Processed %d problems.", processed)

    if not args.dry_run:
        update_readme_stats(PROBLEMS_DIR, counts)


if __name__ == "__main__":
    main()
