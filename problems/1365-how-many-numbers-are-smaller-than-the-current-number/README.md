# 1365. How Many Numbers Are Smaller Than the Current Number

**Difficulty:** Easy | **Language:** CPP | **Tags:** Array, Hash Table, Sorting, Counting Sort

🔗 [View on LeetCode](https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/)

---

## 📝 Problem Statement

Given the array `nums`, for each `nums[i]` find out how many numbers in the array are smaller than it. That is, for each `nums[i]` you have to count the number of valid `j's` such that `j != i` **and** `nums[j] Example 1:

```

**Input:** nums = [8,1,2,2,3]
**Output:** [4,0,1,1,3]
**Explanation:** 
For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3). 
For nums[1]=1 does not exist any smaller number than it.
For nums[2]=2 there exist one smaller number than it (1). 
For nums[3]=2 there exist one smaller number than it (1). 
For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).

```

Example 2:

```

**Input:** nums = [6,5,4,8]
**Output:** [2,1,0,3]

```

Example 3:

```

**Input:** nums = [7,7,7,7]
**Output:** [0,0,0,0]

```

 

**Constraints:**

	- `2 <= nums.length <= 500`
	- `0 <= nums[i] <= 100`

---

## 🚀 My Solution

- **Language:** CPP
- **Runtime:** 9 ms
- **Memory:** 14.2 MB


## 💡 Hints

1. Brute force for each array element.
2. In order to improve the time complexity, we can sort the array and get the answer for each array element.

---

*Auto-synced by [DSA-Progress](https://github.com/AnubhavKiroula/DSA-Progress)*
