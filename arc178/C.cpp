#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n, l;
int dp[200010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int w = 0; char ch = 0;
	while (!isdigit(ch)) w |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (w) x = -x;

}

int main() {
	readx(n); readx(l);
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	
	for (int i = 1; i < l; i++) {
		if (1LL * i * (l - i) > 200004LL) 
			break;
		int wi = i * (l - i);
		for (int j = 0; j + wi <= 200004LL; j++) {   // 根号
			dp[j + wi] = min(dp[j + wi], dp[j] + 1);
		}
	}
	
	int a;
	for (int i = 1; i <= n; i++) {
		readx(a);
		if (dp[a] > 200010) {
			puts("-1");
		} else {
			printf("%d\n", dp[a]);
		}
	}
}

/*
Solution:
  考虑对 B 进行任意排序其实不影响答案，而对 sum of abs 进行变形的前提是去掉这个绝对值号
  则首先可以对 B 进行从小到大排序，这样我们可以直接把绝对值号去掉，但也对构造的 B 提出了有序限制。
  考虑一个有序的 B 的最小值必为 0，否则可以对 B 全体全部 -1。
  考虑如何对 sum[i=1..n][j=1..i-1](Bi-Bj) 进行变形。
  实际上对于每个 Bi - Bj，可以将其拆分为基本的 (B[i]-B[i-1])+(B[i-1]-B[i-2])...
  那么题目中的求和式子就变成了 sum[i=1..n]w[i](B[i]-B[i-1]) 这样的一种形式。
  这个形式有利于统计贡献。同时由于我们对 B 做了排序，实际上每个 B[i]-B[i-1] 这个基本元素都是正的。
  因为我们要构造 B'（B 的差分数组）去满足和式，实际上这是个裸的类 01 背包问题。
  要背的是 w[i] = (i)(n-i)
  还剩一个限制没考虑，考虑最大值的限制实际上被转化成最小化 B' 之和的限制。
  这个在做背包的时候实际上是自然满足的。
  我们可以直接对着 max(A) 做背包，而不用每次询问单独做一次。
*/