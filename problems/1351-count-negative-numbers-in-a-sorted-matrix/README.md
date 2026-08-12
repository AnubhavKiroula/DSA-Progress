# 1351. Count Negative Numbers in a Sorted Matrix

**Difficulty:** Easy | **Language:** CPP | **Tags:** Array, Binary Search, Matrix

🔗 [View on LeetCode](https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/)

---

## 📝 Problem Statement

Given a `m x n` matrix `grid` which is sorted in non-increasing order both row-wise and column-wise, return *the number of **negative** numbers in* `grid`.

 

Example 1:

```

**Input:** grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
**Output:** 8
**Explanation:** There are 8 negatives number in the matrix.

```

Example 2:

```

**Input:** grid = [[3,2],[1,0]]
**Output:** 0

```

 

**Constraints:**

	- `m == grid.length`
	- `n == grid[i].length`
	- `1 <= m, n <= 100`
	- `-100 <= grid[i][j] <= 100`

 

**Follow up:** Could you find an `O(n + m)` solution?

---

## 🚀 My Solution

- **Language:** CPP
- **Runtime:** 0 ms
- **Memory:** 14.2 MB


## 💡 Hints

1. Use binary search for optimization or simply brute force.

---

*Auto-synced by [DSA-Progress](https://github.com/AnubhavKiroula/DSA-Progress)*
