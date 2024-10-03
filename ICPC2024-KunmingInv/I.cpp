#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

char ss[1000010];
int n;
int r_end[1000010], l_end[1000010];
int pfix[1000010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int_t k = 1; char ch = 0;
	while (ch < '0' || ch > '9') { ch = getchar(); if (ch == '-') k = -1; }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	x *= k;
}

int rsum(int L, int R) {
    if (L > R) return 0;
    return pfix[R] - pfix[L - 1];
}

int fill_s(int len) {
    return len / 2;
}

void Solve() {
	scanf("%s", ss + 1);
    n = strlen(ss + 1);
    for (int i = n + 1; i <= 2 * n; i++) {
        ss[i] = ss[i - n];
    }
    int nn = 2 * n;
    
    bool all_same = true;
    for (int i = 1; i <= n; i++) {
        if (ss[i] != ss[1]) {
            all_same = false;
            break;
        }
    }
    if (all_same) {
        printf("%d\n", fill_s(n));
        return;
    }
    
    for (int L = 1; L <= nn; L++) {
        int R = L;
        while (R <= nn && ss[R] == ss[R + 1]) R++;
        for (int i = L; i <= R; i++) {
            r_end[i] = R;
            l_end[i] = L;
        }
        L = R;
    }
    // for (int i = 1; i <= nn; i++) {
    //     printf("[%d %d]\n", l_end[i], r_end[i]);
    // }
    
    // calc ans pfix
    for (int i = 1; i <= nn; i++) {
        int pre = l_end[i] - 1;
        pfix[i] = pfix[pre] + fill_s(i - l_end[i] + 1);
    }
    
    int ans = 1e9;
    for (int L = 1; L <= n; L++) {
        int R = L + n - 1;
        int tans = 0;
        tans += rsum(r_end[L] + 1, l_end[R] - 1);
        tans += fill_s(r_end[L] - L + 1) + fill_s(R - l_end[R] + 1);
        ans = min(ans, tans);
    }
    printf("%d\n", ans);
}

void Clear() {
	for (int i = 0; i <= 2 * n + 5; i++) {
        ss[i] = 0;
        r_end[i] = 0;
        l_end[i] = 0;
        pfix[i] = 0;
    }
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		Solve();
		Clear();
	}
}
