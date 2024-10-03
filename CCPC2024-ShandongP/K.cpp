#include <bits/stdc++.h>
typedef long long ll;
using namespace std;



template<typename int_t>
void readx(int_t &x) {
	x = 0; int_t k = 1; char ch = 0;
	while (ch < '0' || ch > '9') { ch = getchar(); if (ch == '-') k = -1; }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	x *= k;
}


void Solve() {
    int n;
    readx(n);
    puts("Yes");
    for (int i = 1; i <= n - 2; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d%c", i, j == n ? '\n' : ' ');
        }
    }
    int start = n - 2;
    int last_4 = n * 2 - 3;
    for (int i = 1; i <= n - 2; i++) {
        printf("%d ", start + i);
    }
    printf("%d %d\n", last_4, last_4 + 1);
    
    for (int i = 1; i <= n - 2; i++) {
        printf("%d ", start + i);
    }
    printf("%d %d\n", last_4 + 2, last_4 + 3);
    
}

void Clear() {
    
}

int main() {
	// int T; scanf("%d", &T);
	// while (T--) {
		Solve();
	// 	Clear();
	// }
}
