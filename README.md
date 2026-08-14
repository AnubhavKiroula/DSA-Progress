# 🧠 DSA-Progress

> Automated sync of my LeetCode solutions (C++, Python, SQL) with structured problem statements, constraints, and latest accepted code — powered by GitHub Actions.

[![LeetCode Sync](https://github.com/AnubhavKiroula/DSA-Progress/actions/workflows/leetcode-sync.yml/badge.svg)](https://github.com/AnubhavKiroula/DSA-Progress/actions/workflows/leetcode-sync.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

---

## 📌 Introduction

This repository automatically tracks my Data Structures & Algorithms journey by syncing accepted LeetCode submissions into organized folders. Each problem gets its own folder containing:

- A `README.md` with the problem title, difficulty, full statement, constraints, and examples
- A solution file with the latest accepted submission

---

## ⚙️ Automation

GitHub Actions runs a Python sync script **daily at midnight UTC** (and can be triggered manually). The workflow:

1. Checks out the repository
2. Fetches latest accepted submissions from the LeetCode GraphQL API (authenticated via `LEETCODE_SESSION` cookie)
3. Creates or updates problem folders with the solution and README
4. Commits and pushes only if there are changes

To trigger a manual sync: **Actions → LeetCode Sync → Run workflow**

---

## 💻 Languages Supported

| Language | Extension | Folder |
|----------|-----------|--------|
| C++      | `.cpp`    | `problems/<slug>/` |
| Python   | `.py`     | `problems/<slug>/` |
| SQL      | `.sql`    | `problems/<slug>/` |

---

## 📁 Repository Structure

```
DSA-Progress/
├── .github/
│   └── workflows/
│       └── leetcode-sync.yml      # GitHub Actions workflow
├── scripts/
│   ├── backfill.py                # One-time backfill of past submissions
│   └── sync.py                   # Daily sync script (used by Actions)
├── problems/
│   ├── 0001-two-sum/
│   │   ├── README.md              # Problem statement, constraints, examples
│   │   └── 0001-two-sum.cpp       # Latest accepted solution
│   ├── 0002-add-two-numbers/
│   │   ├── README.md
│   │   └── 0002-add-two-numbers.py
│   └── ...
├── .gitignore
├── LICENSE
└── README.md
```

---

## 🔐 Secrets Setup

You need two GitHub repository secrets for the automation to work:

### 1. `LEETCODE_SESSION`

**Purpose:** Authenticates the script to fetch your submissions from LeetCode.

**How to get it:**
1. Log in to [leetcode.com](https://leetcode.com) in your browser
2. Open **Developer Tools** → **Application** tab → **Cookies** → `https://leetcode.com`
3. Find the cookie named `LEETCODE_SESSION` and copy its value

**How to add it:**
1. Go to your GitHub repo → **Settings** → **Secrets and variables** → **Actions**
2. Click **New repository secret**
3. Name: `LEETCODE_SESSION`, Value: *(paste the cookie value)*

---

### 2. `GH_TOKEN`

**Purpose:** Allows GitHub Actions to commit and push changes to this repo.

**How to get it:**
1. Go to GitHub → **Settings** → **Developer settings** → **Personal access tokens** → **Tokens (classic)**
2. Click **Generate new token (classic)**
3. Give it a name (e.g., `leetcode-sync`), set expiration, and check the **`repo`** scope
4. Click **Generate token** and copy it

**How to add it:**
1. Go to your GitHub repo → **Settings** → **Secrets and variables** → **Actions**
2. Click **New repository secret**
3. Name: `GH_TOKEN`, Value: *(paste the token)*

---

## 🚀 One-Time Backfill

To import all your existing (~74) solved problems into the repo structure, run the backfill script locally:

```bash
# 1. Clone the repo and navigate to it
git clone https://github.com/AnubhavKiroula/DSA-Progress.git
cd DSA-Progress

# 2. Install dependencies
pip install requests python-dotenv

# 3. Copy the example env file and fill in your credentials
cp scripts/.env.example .env

# 4. Run the backfill
python scripts/backfill.py

# 5. Push changes
git add .
git commit -m "chore: backfill all existing LeetCode solutions"
git push
```

---

## 📊 Stats

<!-- Stats are auto-updated by the sync workflow -->
| Metric | Count |
|--------|-------|
| Total Problems Solved | 80 |
| C++ Solutions | 79 |
| Python Solutions | 1 |
| SQL Solutions | 0 |

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).
