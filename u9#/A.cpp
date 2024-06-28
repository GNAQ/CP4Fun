#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int mod = 998244353;

int n, a;
int dp[310][30010];
int dp2[30010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int w = 0; char ch = 0;
	while (!isdigit(ch)) w |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (w) x = -x;

}

ll fastpow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

void Solve() {
	readx(n); readx(a);
	a *= 100;
	int base = fastpow(101, mod - 2);
	
	dp[0][0] = 1;
	dp2[0] = dp[0][0];
	for (int j = 1; j <= a; j++) {
		dp2[j] = 0;
		dp2[j] = (dp2[j - 1] + dp[0][j]) % mod;
		if (j > 100) 
			dp2[j] = (dp2[j] - dp[0][j - 101] + mod) % mod;
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= a; j++) {
			// for (int k = 0; k <= 100; k++) {
			// 	if (j >= k) {
			// 		dp[i][j] = (dp[i][j] + 1LL * dp[i - 1][j - k] * base % mod) % mod;
			// 	} else {
			// 		break;
			// 	}
			// }
			dp[i][j] = 1LL * dp2[j] * base % mod;
		}
		dp2[0] = dp[i][0];
		for (int j = 1; j <= a; j++) {
			dp2[j] = (dp2[j - 1] + dp[i][j]) % mod;
			if (j > 100) 
				dp2[j] = (dp2[j] - dp[i][j - 101] + mod) % mod;
		}
	}
	
	int ans = 0;
	for (int i = 0; i < a; i++) {
		ans = (ans + dp[n][i]) % mod;
	}
	ans = (1 - ans + mod) % mod;
	printf("%lld\n", ans);
}


int main() {
	Solve();
}
