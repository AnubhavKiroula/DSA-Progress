# 771. Jewels and Stones

**Difficulty:** Easy | **Language:** CPP | **Tags:** Hash Table, String

🔗 [View on LeetCode](https://leetcode.com/problems/jewels-and-stones/)

---

## 📝 Problem Statement

You're given strings `jewels` representing the types of stones that are jewels, and `stones` representing the stones you have. Each character in `stones` is a type of stone you have. You want to know how many of the stones you have are also jewels.

Letters are case sensitive, so `"a"` is considered a different type of stone from `"A"`.

 

Example 1:

```
**Input:** jewels = "aA", stones = "aAAbbbb"
**Output:** 3

```Example 2:

```
**Input:** jewels = "z", stones = "ZZ"
**Output:** 0

```
 

**Constraints:**

	- `1 <= jewels.length, stones.length <= 50`
	- `jewels` and `stones` consist of only English letters.
	- All the characters of `jewels` are **unique**.

---

## 🚀 My Solution

- **Language:** CPP
- **Runtime:** 1 ms
- **Memory:** 8.8 MB


## 💡 Hints

1. For each stone, check if it is a jewel.

---

*Auto-synced by [DSA-Progress](https://github.com/AnubhavKiroula/DSA-Progress)*
