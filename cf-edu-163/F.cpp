#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 998244353;
int frac[1000010], ifrac[1000010];
int pfc[1000010];
int n, q;
int a[1000010], b[1000010];

ll fastpow(ll a, ll b, ll mod) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

ll C(ll _n, ll _m) {
	if (_n < _m) return 0;
	return 1ll * frac[_n] * ifrac[_m] % mod * ifrac[_n - _m] % mod;
}

ll geta(int l, int r) {
	return a[r] - a[l - 1];
}

ll getb(int l, int r) {
	return b[r] - b[l - 1];
}

void Solve() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
	}
	
	// prefix sum
	for (int i = 2; i <= n; i++) {
		a[i] += a[i - 1];
		b[i] += b[i - 1];
	}
	
	// init pfc
	pfc[0] = 1;
	for (int i = 1; i <= b[n]; i++) {
		pfc[i] = (C(b[n], i) + pfc[i - 1]) % mod;
	}
	
	int l, r;
	for (int qq = 1; qq <= q; qq++) {
		scanf("%d%d", &l, &r);
		ll qk = 2 * geta(l, r) - a[n];
		ll lx = getb(l, r);
		ll ly = b[n] - lx;
		ll ans = 0;
		if (qk + lx <= 0) {
			printf("0\n");
			continue;
		}
		ans = fastpow(fastpow(2, b[n], mod), mod - 2, mod);
		ans = ans * pfc[min<int>(qk + lx - 1, b[n])] % mod;
		printf("%lld\n", ans);
	}
}

void Clear() {
	
}

int main() {
	frac[0] = 1;
	for (int i = 1; i <= 1e6; i++) {
		frac[i] = 1ll * frac[i - 1] * i % mod;
	}
	ifrac[1000000] = fastpow(frac[1000000], mod - 2, mod);
	for (int i = 999999; i >= 0; i--) {
		ifrac[i] = 1ll * ifrac[i + 1] * (i + 1) % mod;
	}
	
	Solve();
	Clear();
}

/*
Solution:
	先套个前缀和
	考虑记 X = 某个 event 中 [L, R] 内部中 1 的个数，Y 是外部 1 的个数，
	则此题实际上是在问 Pr(X - Y + Kqi > 0)，但 +X-Y 和 +X+Y 是不一样的。
	后者可以直接捏在一起预处理前缀和，前者两个变量对概率的影响是反向的，难以处理……
	考虑题中的随机变量的定义函数 X=phi(event)，其中 event 中的每个元素是 binary 的。
	在通常的过程中，我们数贡献的时候是以一个全 0 元素的 trivial 的 event 作为基底，然后数多出来的 1。
	但这次如果我们考虑 X 的时候，把它的定义函数改一下，把贡献做成以 1 为基础减去 0 出现的次数，
	这样实际上是我们得到了一个 X' = -X，这样我们实际上就可以求 Pr(-X - Y + Kqi > 0) 了
	然后我们就可以让 Z = -X-Y，对 Z 的 Pr(Kqi > Z) 的计数就变成了一个前缀和 sum[i=0..Kqi+maxX-1]C(sumB, i)
	乘上每个事件的基础概率 1/2^sumB 就好了
	G 有时间可以补一下。
*/