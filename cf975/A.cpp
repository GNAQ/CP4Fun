#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, a[1010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int w = 0; char ch = 0;
	while (!isdigit(ch)) w |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (w) x = -x;

}



void Solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		// sel i
		int cnt = 1;
		int vmax = a[i];
		for (int j = i - 2; j > 0; j -= 2) {
			vmax = max(vmax, a[j]);
			cnt++;
		}
		for (int j = i + 2; j <= n; j += 2) {
			vmax = max(vmax, a[j]);
			cnt++;
		}
		ans = max(ans, vmax + cnt);
	}
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
A. 考虑选定某个位置作为最大值之后，剩下的红色元素肯定是贪心选。于是实际上只有奇下标最大值和偶下标最大值有用。
*/