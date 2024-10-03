#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll p2[40];
ll per[1000010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int_t k = 1; char ch = 0;
	while (ch < '0' || ch > '9') { ch = getchar(); if (ch == '-') k = -1; }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	x *= k;
}

void Solve() {
    ll n;
    int llg2 = 0;
    readx(n);
    if (n == 1) {
        puts("impossible");
        return;
    }
    
    int xx = 1;
    deque<int> res;
    per[0] = 1;
    per[1] = 0;
    for (int i = 2; i < n; i++) {
        res.push_back(i);
    }
    for (int i = 2; i < n; i++) {
        if ((xx ^ res.front()) == 0 && res.size() == 1) {
            puts("impossible");
            return;
        }
        if ((xx ^ res.front()) == 0) {
            int t = res.front();
            res.pop_front();
            per[i] = res.front();
            res.pop_front();
            res.push_front(t);
        }
        else {
            per[i] = res.front();
            res.pop_front();
        }
        xx ^= per[i];
    }
    for (int i = 0; i < n; i++) {
        printf("%d%c", per[i], " \n"[i == n - 1]);
    }
    return;
}

void Clear() {
	
}

int main() {
    p2[0] = 1;
    for (int i = 1; i <= 38; i++) {
        p2[i] = p2[i - 1] * 2;
    }
    
	int T; scanf("%d", &T);
	while (T--) {
		Solve();
		Clear();
	}
}
