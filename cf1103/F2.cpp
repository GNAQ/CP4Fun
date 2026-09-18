#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e9+7;
int a[100010];
int buc[500010];
int bucp[500010]; // reverse map of prime_xs
vector<int> appear;
vector<pair<int,int>> prime_xs;

int frac[2200010], ifrac[2200010];

ll dp[30][30][30];

ll C(int _n, int _m) {
	return (1LL * frac[_n] * ifrac[_m] % mod * ifrac[_n - _m]) % mod;
}

ll fastpow(ll x, ll p) {
	ll r = 1;
	while (p) {
		if (p & 1) r = r * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return r;
}

void init() {
	frac[0] = 1;
	ifrac[0] = 1;
	for (int i = 1; i <= 2200000; i++) {
		frac[i] = (1LL * frac[i - 1] * i) % mod;
	}
	
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, x;
		cin >> n >> x;
		int x_pos_cnt = 0;
		// deal with x first
		{
			int q = x, lim = sqrt(x) + 1, cnt = 0;
			for (int j = 2; j <= lim ;j++) {
				cnt = 0;
				while (q % j == 0) {
					cnt++;
					q = q / j;
				}
				if (cnt > 0) {
					prime_xs.push_back(pair<int, int>(j, cnt));
					bucp[q] = prime_xs.size();
				}
			}
			if (q > 1) {
				prime_xs.push_back(pair<int, int>(q, 1));
				bucp[q] = prime_xs.size();
			}
		}
		for (int i = 1; i <= prime_xs.size(); i++) {
			for (int j = 0; j <= 23; j++) {
				for (int k = 0; k <= prime_xs[i - 1].second + 1; k++) {
					dp[i][j][k] = 0;
				}
			}
			dp[i][0][0] = 1;
		}
		
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			int q = a[i];
			int lim = sqrt(q) + 1;
			for (int j = 2; j <= lim; j++) {
				int cnt = 0;
				while (q % j == 0) {
					if (buc[j] == 0) {
						appear.push_back(j);
					}
					buc[j]++;
					cnt++;
					q = q / j;
				}
				// update dp
				if (bucp[q] != 0) {
					int idx = bucp[q];
					printf("Solving %d-th prime with a[%d]\n", idx, i);
					int lim = prime_xs[idx - 1].second;
					for (int k = 3; k >= 0; k--) {
						for (int l = lim; l >= 0; l--) {
							if (k == 0 && l == 0) continue;
							ll adv = 0;
							if (k <= cnt) { // 自己做最高的 k，从前面抓凑剩下的 l
								for (int u = 0; u <= l && u <= k; u++) {
									// if (u > l - u)
									adv = (adv + dp[idx][u][l - u]) % mod;
								}
								printf("contrib %d to become k\n", adv);
							}
							// 自己做 l，注意这样要拿少于等于k个
							for (int u = 1; u <= cnt && u <= k && u <= l; u++) { 
								adv = (adv + dp[idx][k][l - u]);
							}
							dp[idx][k][l] = (dp[idx][k][l] + adv) % mod;
							printf("Update dp[%d][%d][%d] to %lld\n", idx, k, l, dp[idx][k][l]);
						}
					}
				}
			}
			if (q > 1) {
				if (buc[q] == 0) {
					appear.push_back(q);
				}
				buc[q]++;
			}
		}
		
		ll ans = 1;
		for (auto v : appear) {
			if (bucp[v] == 0) {
				ans = (1LL * ans * (buc[v] + 1)) % mod;
			}
			buc[v] = 0;
		}
		for (auto v : prime_xs) {
			printf("![%d %d]\n", v.first, v.second);
			ll tmp = 0, lim = v.second, idx = bucp[v.first];
			for (int i = 1; i <= 23; i++) { // enum k 
				tmp = (tmp + dp[idx][i][lim]) % mod;
			}
			ans = (1LL * ans * tmp);
		}
		cout << ans << endl;
		
		for (auto px : prime_xs) bucp[px.first] = 0;
		appear.clear();
		appear.shrink_to_fit();
		prime_xs.clear();
		prime_xs.shrink_to_fit();
	}
}