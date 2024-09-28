#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n, k, ai[200010];
ll max_ai = 0, m;
ll sum_ai = 0;

ll succ(ll sum, ll v) {
	ll h = sum / v + (sum % v != 0);
	return h;
}

void Solve() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &ai[i]);
		max_ai = max(max_ai, ai[i]);
		sum_ai += ai[i];
		if (ai[i] > 0) 
			m++;
	}
	for (ll v = n; v; v--) {
		ll h = max(succ(sum_ai, v), max_ai);
		ll tot = h * v;
		ll need_k = tot - sum_ai;
		if (need_k <= k) {
			printf("%lld\n", v);
			return;
		}
	}
	printf("%lld\n", 1LL);
}

void Clear() {
	for (int i = 0; i <= n + 2; i++) 
		ai[i] = 0;
	max_ai = 0;
	m = 0;
	sum_ai = 0;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		Solve();
		Clear();
	}
}

/*
C. 首先读完题可以发现对于每个高度 v，最少牌堆数是 max(maxAi, sumAi/v上取整）。
则，若牌堆数确定，考虑“依次取每类牌，贪心地进行铺放（横着铺），”是一定不冲突的。
这是因为每类牌的张数都小于牌堆数。故只需要判断 k 够不够用即可。
*/