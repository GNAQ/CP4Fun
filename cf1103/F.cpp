#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e9+7;
int a[100010];
int buc[500010];
vector<int> appear;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, x;
		cin >> n >> x;
		int max_ai = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			max_ai = max(max_ai, a[i]);
			int q = a[i];
			int lim = sqrt(q) + 1;
			for (int j = 2; j <= lim; j++) {
				while (q % j == 0) {
					if (buc[j] == 0) {
						appear.push_back(j);
					}
					buc[j]++;
					q = q / j;
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
			ans = (1LL * ans * (buc[v] + 1)) % mod;
			buc[v] = 0;
		}
		cout << ans << endl;
		
		appear.clear();
		appear.shrink_to_fit();
	}
}