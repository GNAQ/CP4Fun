

/*
	Solution
	将数组视为点集，按照题目的条件在点之间连边，这是一个典型的 DAG
	考虑题目实际上就是在问这个 DAG 的固定起点路径数。
	考虑 dp: dp[v] = sum[u -e> v](dp[u])，可以做出答案
	这个 DAG 的边集是有特殊结构的，考虑每个 u 连出去的边 e(u, v): u mod Au == v mod Au && v > u
	用一个式子就能求出 u 贡献到的所有 v。这种贡献形式，实际上可以用 (Au, u) 这个二元组来描述。
	在这种情况下，我们考虑把这个 dp 反过来转移：foreach(u=1..n)[u -e> v] dp[v] += dp[u]
	则可以用一个数据结构维护这种过程。考虑一个二维数据结构：v[i][j] 表示 dp 枚举到当前这个 u 为止
	前面的所有点给的贡献中 A = i 且 mod A = j 的贡献总共是多少。
	这样获取当前 dp[u] 值的复杂度是 O(A) 的，向后转移是 O(1) 的
	发现这样是 O(AN) 的过不去，这题的连边，数论味这么重，考虑对 A 上个根号分治。
	> 根号暴力，< 根号用上述做法就可以了。
*/