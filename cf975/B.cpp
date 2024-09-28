#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, q;
ll xi[100010], ki[100010];

map<ll, ll> pq;

template<typename int_t>
void readx(int_t &x) {
	x = 0; int w = 0; char ch = 0;
	while (!isdigit(ch)) w |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (w) x = -x;

}



void Solve() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &xi[i]);
	}
	for (int i = 1; i <= q; i++) {
		scanf("%lld", &ki[i]);
	}
	
	for (int i = 1; i < n; i++) {
		ll p = i;
		ll q = (n - i);
		pq[p * q] += (xi[i + 1] - xi[i] - 1);
		ll r_cross = p * (q - 1) + p + (q - 1);
		pq[r_cross] += 1;
	}
	ll one_cross = n - 1;
	pq[one_cross] += 1;
	
	for (int i = 1; i <= q; i++) {
		printf("%lld%c", pq[ki[i]], " \n"[i == q]);
	}
}

void Clear() {
	pq.clear();
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		Solve();
		Clear();
	}
}

/*
B. 考虑某个点被线段跨过的条数，发现实际上是左侧点数 q 乘上右侧点数 p。
于是 q×p 只有至多 n 种。提前算好存到 map 里面，询问的时候现查。
注意题目是闭区间，区间端点要单独算，不是 p×q。
*/