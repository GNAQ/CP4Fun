#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll ansx, ansy;
int n, m, mat[1010][1010];
vector<int> v;
int cxu[1000010], cxd[1000010], cyl[1000010], cyr[1000010];
int nxu[1000010], nxd[1000010], nyl[1000010], nyr[1000010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int w = 0; char ch = 0;
	while (!isdigit(ch)) w |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (w) x = -x;

}


void Solve() {
	readx(n); readx(m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			readx(mat[i][j]);
			v.push_back(mat[i][j]);
		}
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			mat[i][j] = lower_bound(v.begin(), v.end(), mat[i][j]) - v.begin() + 1;
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cxd[mat[i][j]] += i;
			cyr[mat[i][j]] += j;
			nxd[mat[i][j]] += 1;
			nyr[mat[i][j]] += 1;
		}
	}
	// calc  ansx;
	for (int i = 1; i <= n; i++) {
		// clear cxd
		for (int j = 1; j <= m; j++) {
			cxd[mat[i][j]] -= i;
			nxd[mat[i][j]] -= 1;
		}
		for (int j = 1; j <= m; j++) {
			int c = mat[i][j];
			int tmp = cxd[c] - (nxd[c] * i) + (nxu[c] * i) - cxu[c];
			ansx += tmp;
		}
		// add cxu
		for (int j = 1; j <= m; j++) {
			cxu[mat[i][j]] += i;
			nxu[mat[i][j]] += 1;
		}
	}
	// calc ansy
	for (int j = 1; j <= m; j++) {
		// clear cxd
		for (int i = 1; i <= n; i++) {
			cyr[mat[i][j]] -= j;
			nyr[mat[i][j]] -= 1;
		}
		for (int i = 1; i <= n; i++) {
			int c = mat[i][j];
			int tmp = cyr[c] - (nyr[c] * j) + (nyl[c] * j) - cyl[c];
			ansy += tmp;
		}
		// add cxu
		for (int i = 1; i <= n; i++) {
			cyl[mat[i][j]] += j;
			nyl[mat[i][j]] += 1;
		}
	}
	
	printf("%lld\n", ansx + ansy);
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
