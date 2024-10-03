#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n, m, k;
ll ai[1010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int_t k = 1; char ch = 0;
	while (ch < '0' || ch > '9') { ch = getchar(); if (ch == '-') k = -1; }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	x *= k;
}


void Solve() {
    readx(n); readx(k);
    for (int i = 1; i <= n; i++) readx(ai[i]);
    readx(m);
    
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += ai[i] / k;
        ai[i] %= k;
    }
    sort(ai + 1, ai + n + 1, greater<ll>());
    for (int i = 1; i <= n; i++) {
        if (m >= (k - ai[i])) {
            ans++;
            m -= (k - ai[i]);
        }
    }
    if (m > 0) {
        ans += m / k;
    }
    printf("%lld\n", ans);
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
