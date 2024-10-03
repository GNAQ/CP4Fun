#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

char ss[1000010];
int n;

template<typename int_t>
void readx(int_t &x) {
	x = 0; int_t k = 1; char ch = 0;
	while (ch < '0' || ch > '9') { ch = getchar(); if (ch == '-') k = -1; }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	x *= k;
}


void Solve() {
	scanf("%s", ss + 1);
    n = strlen(ss + 1);
    ss[0] = ss[n];
    
    for (int i = 0; i < n; i++) {
        if (ss[i] == ss[i + 1]) {
            printf("%d\n", i);
            return;
        }
    }
    printf("-1\n");
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
