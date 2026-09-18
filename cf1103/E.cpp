#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int a[10010];
int buc[10010], ok[6002]; // pos len
int rev[6002][6002];

int main() {
	int t;
	int n;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		int ans = 0;
		for (int l = 1; l <= n; l++) {
			int minv = a[l], maxv = a[l];
			buc[a[l]] = true;
			ok[1] = minv;
			rev[a[l]][a[l]] = l;
			for (int r = l + 1; r <= n; r++) {
				if (buc[a[r]]) {
					break;
				}
				buc[a[r]] = true;
				minv = min(minv, a[r]);
				maxv = max(maxv, a[r]);
				if (maxv - minv == r - l) {
					ok[r - l + 1] = minv;
					if (rev[minv][maxv] == 0) 
						rev[minv][maxv] = l;
				}
			}
			
			// enum ans (len from 1 to end)
			for (int i = 1; i <= (n - l + 1); i++) {
				if (ok[i] > 0) {
					int bar = (l - i);
					// find (minv - len)
					int search_v = ok[i] - i;
					if (search_v >= 1) {
						int candi = rev[search_v][search_v + i - 1];
						if (candi > 0 && candi <= bar) {
							// printf("upd from [%d, %d] - [%d, %d]\n", candi, candi+i-1, l, l+i-1);
							ans = max(ans, i);
						}
					}
					// find maxv + len
					search_v = ok[i] + 2 * i - 1;
					if (search_v <= n) {
						int candi = rev[search_v - i + 1][search_v];
						if (candi > 0 && candi <= bar) {
							// printf("upd from [%d, %d] - [%d, %d]\n", candi, candi+i-1, l, l+i-1);
							ans = max(ans, i);
						}
					}
				}
			}
			// reset bucket
			for (int i = 1; i <= n; i++) {
				buc[i] = ok[i] = 0;
			}
		}
		
		cout << ans << endl;
		// reset all
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				rev[i][j] = 0;
			}
		}
	}
	return 0;
}