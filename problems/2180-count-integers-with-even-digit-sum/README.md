# 2180. Count Integers With Even Digit Sum

**Difficulty:** Easy | **Language:** CPP | **Tags:** Math, Simulation

🔗 [View on LeetCode](https://leetcode.com/problems/count-integers-with-even-digit-sum/)

---

## 📝 Problem Statement

Given a positive integer `num`, return *the number of positive integers **less than or equal to*** `num` *whose digit sums are **even***.

The **digit sum** of a positive integer is the sum of all its digits.

 

Example 1:

```

**Input:** num = 4
**Output:** 2
**Explanation:**
The only integers less than or equal to 4 whose digit sums are even are 2 and 4.    

```

Example 2:

```

**Input:** num = 30
**Output:** 14
**Explanation:**
The 14 integers less than or equal to 30 whose digit sums are even are
2, 4, 6, 8, 11, 13, 15, 17, 19, 20, 22, 24, 26, and 28.

```

 

**Constraints:**

	- `1 <= num <= 1000`

---

## 🚀 My Solution

- **Language:** CPP
- **Runtime:** 0 ms
- **Memory:** 7.9 MB


## 💡 Hints

1. Iterate through all integers from 1 to num.
2. For any integer, extract the individual digits to compute their sum and check if it is even.

---

*Auto-synced by [DSA-Progress](https://github.com/AnubhavKiroula/DSA-Progress)*
