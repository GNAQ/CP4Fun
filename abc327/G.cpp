#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll C[1010][1010];
ll g[1010][1010], h[1010][1010], f[1010][1010];
const ll mod = 998244353;

ll fastpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

ll B(ll m, ll k) {
	ll ret = 0;
	for (int i = 0; i <= k; ++i) {
		ll tmp = C[k][i] * fastpow(i, m) % mod;
		if ((k - i) & 1) tmp = -tmp;
		ret = (ret + tmp + mod) % mod;
	}
	return ret;
}

ll G(ll n, ll m) {
	ll ret = 0;
	for (int i = 0; i <= n; i++) {
		ll tmp = C[n][i] * C[i * (n - i)][m] % mod;
		ret = (ret + tmp) % mod;
	}
	return ret;
}

ll H(ll n, ll m) {
	
}

ll F(ll n, ll m) {
	
}


int main() {
	// init combination
	for (int i = 0; i <= 1000; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
	}
	
	ll Ln = 30, Lm = 1e9, Lk = 225;
	for (int i = 1; i <= Ln; i++) {
		for (int j = 0; j <= Lm; j++) {
			g[i][j] = G(i, j);
		}
	}
}

/*
	Solution: （学的官方题解）
	要计数一个可重有向边且点边都有标号的多连通块二分图类似物。但时刻注意数的不是这样图的个数，而是连边序列的方案。
	
	注意到我们有重边，如果考虑要数点有标号简单二分图的话（简单时有各种好的选择性质），我们考虑这样转化：
	首先把题目的答案除掉 2^M，这样相当于每条边都无向了，且除掉之前和之后的方案正好是一对二，不重不漏。
	之后我们把连边序列的边去重，这样每个连边序列就变成了唯一对应的简单二分图。
	那么对于这个二分图来说，映射到它的所有连边序列的个数是 b(M, k)。其中 M 是序列长度，k 是简单边数。
	b(M, k) 是将 M 个有标号球放到 k 个箱子里，不能空放的方案数，这个东西就是 M! * S(M, k)。很经典。
	那么答案 ans(N, M) = sum[k=0..maxEdgeNum](b(M, k) * f(N, k))，其中 f(N, k) 是 N 点 k 边的简单二分图的个数。
	
	我们来考虑怎么数 f(N, k)。我们用一个二维的容斥 DP 去直接推。下列图点都有标号，边都无向无重无标号
	设 g[n][m] 是 n 点 m 边，每个点的颜色是黑、白的图的个数，且每条边只连一对黑—白点。
	直接组合：g[n][m] = sum[i=0..n](C(n, i) * C(i * (n - i), m)) 
	注意到 g 这个东西求的图是有散点的，散点不方便做进一步计数，自然地我们想求左右两侧都精确连通的东西。
	进一步设 h[n][m] 在 g 的条件之上强制此图联通，这是个容斥的斥性 DP：
	h[n][m] = g[n][m] - sum[i=1..n-1][j=0..m](C(n-1, i-1) * h[i][j] * g[n-i][m-j])
	这一步，我们认为 1 号点作为连通区域的根（重标号不改变答案），然后枚举其所在的连通区域的样子。之后以斥性方向把非全联通的图都去掉。
	注意每个简单二分图黑白染色有两种方案（标号 1 染黑色或者白色），所以实际上的简单连通二分图个数是 h(n, m) / 2 才对。
	
	后面就很简单了，我们可以在获得 h(n, m) / 2 之后再装回去变成多连通块图，也是重标号的方式枚举第一块：
	f[n][m] = h[n][m] / 2 + sum[i=1..n-1][j=0..m](C(n-1, i-1) * f[i][j] * h[n-i][m-j] / 2)
	
	最后我们来考虑一下怎么求 b(M, k)，这个东西是 sum[i=0..k]((-1)^{k-i} * C(k, i) * i^M)。
	可以直接从容斥的角度斥出来，也可以斯特林反演。
	
	就做完了。**注意边界，注意取模**
*/