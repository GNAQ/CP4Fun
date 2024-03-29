/*
Solution:
	答案有可二分性，先在 1e12 的范围内二分一下答案。
	对 S 求每个前缀位置的特定字母个数 pre_s[i][char]，然后我们从前到后依次匹配 T 的每个字母 ti。
	我们可以用一个二元组 (a, cur) 表示当前匹配到了 S 的第 a + 1 个循环的第 cur 个坐标。
	这个二元组实际上是有序关系的，于是我们也可以上一个二分，进行贪心匹配。
	总复杂度就做到了 O(nlog^2(n))
*/