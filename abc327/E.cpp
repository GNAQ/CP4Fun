#include <bits/stdc++.h>
using namespace std;
using ll = long long;

double dp[5010][5010]; // 考虑了前 i 个数，并且 k = j 的最佳答案
double deno[5010];
int n, p[10010];

void init_dp() {
	for (int i = 1; i <= n; i++) {
		deno[i] = deno[i - 1] + pow(0.9, i - 1);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
	}
	
	init_dp();
	// 这里倒着 DP
	for (int i = n; i >= 1; i--) {
		for (int j = 1; j <= n - i + 1; j++) {
			dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - 1] + p[i] * pow(0.9, j - 1));
		}
	}
	
	double ans = -1e15;
	for (int k = 1; k <= n; k++) {
		double aans = dp[1][k] / deno[k];
		aans += -1200.0 / sqrt(k);
		ans = max(ans, aans);
	}
	printf("%.10lf\n", ans);
}


/*
	Solution
	注意到可以 n^2 做
	确定下来 k 之后，不确定的就只有式子左上角那一项
	注意到这个式子其实没啥后效性，这样直接 DP 就好了。
*/