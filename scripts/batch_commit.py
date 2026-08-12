#!/usr/bin/env python3
"""
batch_commit.py  —  commit problems/ in batches with LeetHub-style messages.
Run from repo root after backfill but before pushing.
Usage:  python scripts/batch_commit.py [--batch-size 4]
"""

import re
import sys
import subprocess
import argparse
from pathlib import Path

PROBLEMS_DIR = Path("problems")

LANG_NAMES = {
    "cpp":  "C++",
    "py":   "Python",
    "sql":  "SQL",
    "java": "Java",
    "js":   "JavaScript",
    "ts":   "TypeScript",
    "go":   "Go",
    "rs":   "Rust",
}


def git(args: list[str]) -> str:
    result = subprocess.run(
        ["git"] + args, capture_output=True, text=True, check=True
    )
    return result.stdout.strip()


def staged_problem_folders() -> list[Path]:
    """Return list of problem folder Paths that are currently staged."""
    status = subprocess.run(
        ["git", "diff", "--cached", "--name-only"],
        capture_output=True, text=True
    ).stdout.strip().splitlines()

    folders: set[Path] = set()
    for line in status:
        p = Path(line)
        # e.g.  problems/0001-two-sum/README.md  -> problems/0001-two-sum
        if p.parts and p.parts[0] == "problems" and len(p.parts) >= 2:
            folders.add(PROBLEMS_DIR / p.parts[1])
    return sorted(folders)


def read_readme_stats(folder: Path) -> dict:
    """Pull problem number, title, difficulty, runtime, memory from README."""
    readme = folder / "README.md"
    stats = {"fid": "????", "title": folder.name, "difficulty": "",
             "runtime": "", "memory": "", "lang": ""}
    if not readme.exists():
        return stats

    text = readme.read_text(encoding="utf-8")

    # Title line:  # 0001. Two Sum
    m = re.search(r"^#\s+(\d+)\.\s+(.+)$", text, re.MULTILINE)
    if m:
        stats["fid"]   = m.group(1).zfill(4)
        stats["title"] = m.group(2).strip()

    # Difficulty line
    m = re.search(r"\*\*Difficulty:\*\*\s+(\w+)", text)
    if m:
        stats["difficulty"] = m.group(1)

    # Runtime / Memory lines
    m = re.search(r"\*\*Runtime:\*\*\s+(.+)", text)
    if m:
        stats["runtime"] = m.group(1).strip()
    m = re.search(r"\*\*Memory:\*\*\s+(.+)", text)
    if m:
        stats["memory"] = m.group(1).strip()

    # Language — infer from solution file extension
    for f in folder.iterdir():
        if f.name != "README.md":
            stats["lang"] = LANG_NAMES.get(f.suffix.lstrip("."), f.suffix.lstrip(".").upper())
            break

    return stats


def build_message(batch: list[dict]) -> str:
    if len(batch) == 1:
        p = batch[0]
        rt = f"Time: {p['runtime']}, " if p["runtime"] else ""
        mem = f"Space: {p['memory']} - " if p["memory"] else ""
        suffix = "AutoSync" if (rt or mem) else "AutoSync"
        perf = f"{rt}{mem}{suffix}" if (rt or mem) else "AutoSync"
        return f"{perf}\n\n{p['fid']}. {p['title']}"
    else:
        lines = [f"AutoSync: {len(batch)} LeetCode solution(s)", ""]
        for p in batch:
            rt  = p["runtime"] or "N/A"
            mem = p["memory"]  or "N/A"
            diff = f" [{p['difficulty']}]" if p["difficulty"] else ""
            lines.append(f"- {p['fid']}. {p['title']}{diff} | Time: {rt}, Space: {mem}")
        return "\n".join(lines)


def chunks(lst, n):
    for i in range(0, len(lst), n):
        yield lst[i:i + n]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--batch-size", type=int, default=4)
    args = parser.parse_args()

    # Collect all staged problem folders
    folders = staged_problem_folders()
    if not folders:
        # Nothing staged yet — stage everything under problems/
        print("Nothing staged. Staging problems/ now...")
        subprocess.run(["git", "add", "problems/"], check=True)
        folders = staged_problem_folders()

    print(f"Found {len(folders)} staged problem folders. Batch size: {args.batch_size}")
    print(f"That's {-(-len(folders) // args.batch_size)} commits.\n")  # ceil div

    total_committed = 0
    for i, batch_folders in enumerate(chunks(folders, args.batch_size), 1):
        # Stage only this batch
        subprocess.run(["git", "restore", "--staged", "problems/"], check=True)
        for folder in batch_folders:
            subprocess.run(["git", "add", str(folder)], check=True)

        # Build stats list
        batch_stats = [read_readme_stats(f) for f in batch_folders]

        # Commit
        msg = build_message(batch_stats)
        subprocess.run(["git", "commit", "-m", msg], check=True)

        titles = ", ".join(f"{s['fid']}. {s['title']}" for s in batch_stats)
        print(f"  Commit {i}: {titles}")
        total_committed += len(batch_folders)

    print(f"\n✅ Done! {total_committed} problems committed across {i} commits.")
    print("Run:  git push origin main")


if __name__ == "__main__":
    main()
