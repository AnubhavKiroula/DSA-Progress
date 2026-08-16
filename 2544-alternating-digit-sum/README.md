# 2544. Alternating Digit Sum

**Difficulty:** Easy | **Language:** CPP | **Tags:** Math

🔗 [View on LeetCode](https://leetcode.com/problems/alternating-digit-sum/)

---

## 📝 Problem Statement

You are given a positive integer `n`. Each digit of `n` has a sign according to the following rules:

	- The **most significant digit** is assigned a **positive** sign.
	- Each other digit has an opposite sign to its adjacent digits.

Return *the sum of all digits with their corresponding sign*.

 

Example 1:

```

**Input:** n = 521
**Output:** 4
**Explanation:** (+5) + (-2) + (+1) = 4.

```

Example 2:

```

**Input:** n = 111
**Output:** 1
**Explanation:** (+1) + (-1) + (+1) = 1.

```

Example 3:

```

**Input:** n = 886996
**Output:** 0
**Explanation:** (+8) + (-8) + (+6) + (-9) + (+9) + (-6) = 0.

```

 

**Constraints:**

	- `1 9`

 

.spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
}
.spoiler {overflow:hidden;}
.spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
.spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
.spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}

---

## 🚀 My Solution

- **Language:** CPP
- **Runtime:** 0 ms
- **Memory:** 8 MB


## 💡 Hints

1. The first step is to loop over the digits. We can convert the integer into a string, an array of digits, or just loop over its digits.
2. Keep a variable sign that initially equals 1 and a variable answer that initially equals 0.
3. Each time you loop over a digit i, add sign * i to answer, then multiply sign by -1.

---

*Auto-synced by [DSA-Progress](https://github.com/AnubhavKiroula/DSA-Progress)*
