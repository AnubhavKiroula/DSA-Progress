# 1207. Unique Number of Occurrences

**Difficulty:** Easy | **Language:** CPP | **Tags:** Array, Hash Table

🔗 [View on LeetCode](https://leetcode.com/problems/unique-number-of-occurrences/)

---

## 📝 Problem Statement

Given an array of integers `arr`, return `true` *if the number of occurrences of each value in the array is **unique** or *`false`* otherwise*.

 

Example 1:

```

**Input:** arr = [1,2,2,1,1,3]
**Output:** true
**Explanation:** The value 1 has 3 occurrences, 2 has 2 and 3 has 1. No two values have the same number of occurrences.
```

Example 2:

```

**Input:** arr = [1,2]
**Output:** false

```

Example 3:

```

**Input:** arr = [-3,0,1,-3,1,1,1,-3,10,0]
**Output:** true

```

 

**Constraints:**

	- `1 <= arr.length <= 1000`
	- `-1000 <= arr[i] <= 1000`

---

## 🚀 My Solution

- **Language:** CPP
- **Runtime:** 3 ms
- **Memory:** 12.1 MB


## 💡 Hints

1. Find the number of occurrences of each element in the array using a hash map.
2. Iterate through the hash map and check if there is a repeated value.

---

*Auto-synced by [DSA-Progress](https://github.com/AnubhavKiroula/DSA-Progress)*
