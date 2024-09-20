#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m, K;
int dp[200010][7];
char s[200010];
int pre0pos[200010], pfsum[200010];

bool valid(int val) {
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 0; i <= n; i++) {
		dp[i][0] = 0;
	}
	for (int i = val + 1; i <= n; i++) {
		// must select consecutive >=val elements with '0' as outliers
		if (s[i + 1] != '0') {
			for (int j = 1; j <= K; j++) {
				dp[i][j] = dp[i - 1][j];
			}
			continue;
		}
		
		int l = pre0pos[i - val + 1];
		int len = (i - l);
		int cnt0 = len - pfsum[i] + pfsum[l];
		for (int j = 1; j <= K; j++) {
			dp[i][j] = min(dp[i - 1][j], dp[l - 1][j - 1] + cnt0);
		}
	}
	for (int i = 2; i <= n; i++) {
		if (dp[i][K] <= m)
			return true;
	}
	return false;
}

void Solve() {
	scanf("%d%d%d", &n, &m, &K);
	scanf("%s", s + 2);
	n++;
	s[0] = s[1] = s[n + 1] = '0';
	pfsum[0] = 0;
	int prepos = 0;
	for (int i = 1; i <= n; i++) {
		pfsum[i] = pfsum[i - 1] + (s[i] == '1');
		pre0pos[i] = prepos;
		if (s[i] == '0') {
			prepos = i;
		}
	}
	
	int l = 1, r = ((n - 1) - K + 1) / K;
	int ans = -1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (valid(mid)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	printf("%d\n", ans);
}

int main() {
	Solve();
}

/*
Solution:
  观察 K 是很小的，考虑一个 O(knlogn) 的作法。
  考虑二分，把最优化问题变成判定性问题。
  此后题目转变为花费 <=m 次操作，选出 >=K 个长度为 mid 的连续段，且这些段的两端都是 '0'。
  这是个经典的 dp 问题。
  用 dp[i][j] 表示前 i 个字符中选出 j 个长度至少为 mid 的连续段的最小花费，
  想办法构造转移方程即可。
*/