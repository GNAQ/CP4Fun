#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
int n, k, dp[2000010][13], psum[2000010][13];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i <= k; i++) {
		dp[0][0] = 1;
		psum[0][0] = 1;
	}
	
	for (int i = 1; i <= n; i++) {
		dp[i][1] = 1;
		for (int c = 2; c <= min(k, i); c++) {
			if (c != k) {
				if (i != n) {
					dp[i][c] = (dp[i - 1][c - 1]);
					if (i > 3) {
						dp[i][c] = (dp[i][c] + psum[i - 3][c - 1]) % mod;
					}
				} else {
					dp[i][c] = psum[i - 1][c - 1];
				}
			} else {
				if (i != n) {
					dp[i][c] = (dp[i - 1][c - 1] + dp[i - 1][c]) % mod;
					if (i > 3) {
						dp[i][c] = (dp[i][c] + psum[i - 3][c - 1]) % mod;
						dp[i][c] = (dp[i][c] + psum[i - 3][c]) % mod;
					}
				} else {
					dp[i][c] = (psum[i - 1][c - 1] + psum[i - 1][c]) % mod;
				}
			}
		}
		
		// maintain prefix sum
		for (int c = 0; c <= k; c++) {
			psum[i][c] = (psum[i - 1][c] + dp[i][c]) % mod;
		}
	}
	printf("%d\n", dp[n][k]);
}