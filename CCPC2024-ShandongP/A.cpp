#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n, k;
ll ti[1010], li[1010], wi[1010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int_t k = 1; char ch = 0;
	while (ch < '0' || ch > '9') { ch = getchar(); if (ch == '-') k = -1; }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	x *= k;
}

ll calc_cnt(ll id, ll T) {
    ll lp = ti[id] * li[id] + wi[id];
    ll ret = 0;
    ret += (T / lp) * li[id];
    T %= lp;
    if (T >= ti[id] * li[id]) {
        ret += li[id];
    } else {
        ret += T / ti[id];
    }
    return ret;
}

void Solve() {
    readx(n); readx(k);
    for (int i = 1; i <= n; i++) {
        readx(ti[i]); readx(li[i]); readx(wi[i]);
    }
    
    ll L = 0, R = 3e18;
    ll ans = R;
    while (L <= R) {
        ll mid = (L + R) / 2;
        ll cnt = 0;
        for (int i = 1; i <= n; i++) {
            cnt += calc_cnt(i, mid);
            if (cnt >= k) break; // 这里会爆 long long
            // printf("[%d] will print %lld use %lld min\n", i, calc_cnt(i, mid), mid);
        }
        if (cnt >= k) {
            ans = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
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
