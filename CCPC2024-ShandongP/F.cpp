#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
ll suf[500010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int_t k = 1; char ch = 0;
	while (ch < '0' || ch > '9') { ch = getchar(); if (ch == '-') k = -1; }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	x *= k;
}


void Solve() {
    readx(n);
	for (int i = 1; i <= n; i++) {
		readx(suf[i]);
	}
	for (int i = n - 1; i >= 1; i--) {
		suf[i] += suf[i + 1];
	}
	sort(suf + 2, suf + n + 1, greater<ll>());
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += suf[i];
		printf("%lld%c", ans, " \n"[i == n]);
	}
}

void Clear() {
    
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		Solve();
		Clear();
	}
}
