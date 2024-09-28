#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, ai[200010];
int b[200010];

void Solve() {
	scanf("%d", &n);
	int min_pos = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &ai[i]);
		if (ai[i] < ai[min_pos]) min_pos = i;
		b[i] = ai[i];
	}
	
	// check min_pos solutionable
	int x = min_pos;
	for (int i = 2; i < x; i++) {
		b[i] = min(b[i], b[i - 1] - 1);
	}
	for (int i = n - 1; i > x; i--) {
		b[i] = min(b[i], b[i + 1] - 1);
	}
	b[0] = b[n + 1] = 1e9;
	int l = x, r = x, t = 1;
	// printf("!!!%d\n", x);
	// for (int i = 1; i <= n; i++) {
	// 	printf("%d%c", b[i], " \n"[i == n]);
	// }
	while (l > 1 || r < n) {
		t++;
		if (b[l - 1] < t || b[r + 1] < t) {
			printf("0\n");
			return;
		}
		if (b[l - 1] <= b[r + 1]){
			l--;
		}
		else {
			r++;
		}
	}
	
	int ans_r = n, ans_l = 1;
	for (int i = 1; i <= n; i++) {
		ans_r = min(ans_r, i + (ai[i] - 1));
	}
	for (int i = n; i >= 1; i--) {
		ans_l = max(ans_l, i - (ai[i] - 1));
	}
	int ans = max(0, ans_r - ans_l + 1);
	printf("%d\n", ans);
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

/*
D. 考虑用反证法证明此事：如果有解，选 a(i) 值最小的下标 i 作为起点一定是合法解之一。
用同样的反证法证明解一定是连续的，模拟证明策略计算区间长度即可。
*/
