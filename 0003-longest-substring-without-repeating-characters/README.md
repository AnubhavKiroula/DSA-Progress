# 3. Longest Substring Without Repeating Characters

**Difficulty:** Medium | **Language:** CPP | **Tags:** Hash Table, String, Sliding Window

🔗 [View on LeetCode](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

---

## 📝 Problem Statement

Given a string `s`, find the length of the **longest** **substring** without duplicate characters.

 

Example 1:

```

**Input:** s = "abcabcbb"
**Output:** 3
**Explanation:** The answer is "abc", with the length of 3. Note that `"bca"` and `"cab"` are also correct answers.

```

Example 2:

```

**Input:** s = "bbbbb"
**Output:** 1
**Explanation:** The answer is "b", with the length of 1.

```

Example 3:

```

**Input:** s = "pwwkew"
**Output:** 3
**Explanation:** The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

```

 

**Constraints:**

	- `0 5`
	- `s` consists of English letters, digits, symbols and spaces.

---

## 🚀 My Solution

- **Language:** CPP
- **Runtime:** 329 ms
- **Memory:** 81.4 MB


## 💡 Hints

1. There are less than 100 unique characters. We can check all substrings with length at most 100 for example. This is a good enough approximation.

---

*Auto-synced by [DSA-Progress](https://github.com/AnubhavKiroula/DSA-Progress)*
