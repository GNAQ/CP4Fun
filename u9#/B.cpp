#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int mod = 998244353;

int n, l;
ll ai[1010];
ll m;

ll pi[1010], qi[1010];
int pc = 0;

struct ST {
	int x[13];
	bool operator < (const ST &rhs) const {
		for (int i = 1; i <= pc; i++) {
			if (x[i] != rhs.x[i]) return x[i] < rhs.x[i];
		}
		return false;
	}
	void operator+=(const ST& rhs) {
		for (int i = 1; i <= pc; i++) {
			x[i] += rhs.x[i];
		}
	}
	bool operator == (const ST &rhs) const {
		for (int i = 0; i <= pc; i++) {
			if (x[i] != rhs.x[i]) return false;
		}
		return true;
	}
} state[10100];
int stc = 0;
map<ST, int> st2id;
vector<ST> tst[10010];
vector<int> tidr[10010];

int dp[110][110][2010];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int w = 0; char ch = 0;
	while (!isdigit(ch)) w |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (w) x = -x;
}

int fastpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return res;
}

int di[20];
void DFS_ST() {
	stc++;
	for (int i = 1; i <= pc; i++) {
		state[stc].x[i] = di[i];
	}
	if (st2id[state[stc]] != 0) {
		stc--;
		return;
	}
	st2id[state[stc]] = stc;
	
	for (int i = 1; i <= pc; i++) {
		if (di[i] < qi[i]) {
			di[i]++;
			DFS_ST();
			di[i]--;
		}
	}
}

ST get_a_st(int val) {
	ST res;
	for (int i = 1; i <= pc; i++) {
		res.x[i] = 0;
	}
	for (int i = 1; i <= pc; i++) {
		while (val % pi[i] == 0) {
			val /= pi[i];
			res.x[i]++;
		}
	}
	if (val != 1) {
		res.x[0] = -1;
	} else {
		res.x[0] = 0;
	}
	return res;

}

void Solve() {
	readx(n); readx(m); readx(l);
	for (int i = 1; i <= n; i++) readx(ai[i]);
	
	// sp: m == 1
	if (m == 1) {
		int tmp = 0;
		for (int i = 1; i <= n; i++) {
			if (ai[i] == 1) tmp++;
		}
		if (n - tmp <= l && n - tmp >= 1) {
			puts("1");
		} else {
			puts("0");
		}
		return;
	}
	
	// prime factorization of m
	ll mm = m;
	ll p = 2;
	while (p * p <= mm) {
		if (mm % p == 0) {
			pi[++pc] = p;
			while (mm % p == 0) {
				mm /= p;
				qi[pc]++;
			}
		}
		p++;
	}
	if (mm > 1) {
		pi[++pc] = mm;
		qi[pc] = 1;
	}
	DFS_ST();
	// transfer states
	ST mst;
	for (int i = 1; i <= pc; i++) mst.x[i] = qi[i];
	for (int i = 1; i <= stc; i++) {
		for (int j = 1; j <= stc; j++) {
			ST tmp = state[i]; tmp += state[j];
			bool flag = true;
			for (int k = 1; k <= pc; k++) {
				if (tmp.x[k] > mst.x[k]) {
					flag = false;
					break;
				}
			}
			if (flag) {
				tst[i].push_back(state[j]);
				tidr[i].push_back(st2id[tmp]);
			}
		}
	}
	// get ai st
	ST ast[110];
	for (int i = 1; i <= n; i++) {
		ast[i] = get_a_st(ai[i]);
	}
	
	// dp
	dp[0][0][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= l; j++) {
			for (int k = 1; k <= stc; k++) {
				int nk;
				ST prest = state[k];
				// put ai
				if (ast[i].x[0] != -1) {
					prest += ast[i];
					nk = st2id[prest];
					dp[i][j][nk] = (dp[i][j][nk] + dp[i - 1][j][k]) % mod;
				}
					
				// put some random bi, including 1 (st id == 1) -> dp[i][j + 1]
				for (int ii = 0; ii < tst[k].size(); ii++) {
					// should not be the same as ai
					if (tst[k][ii] == ast[i]) 
						continue;
					int nk = tidr[k][ii];
					dp[i][j + 1][nk] = (dp[i][j + 1][nk] + dp[i - 1][j][k]) % mod;
				}
			}
		}
	}
	
	// calc ans;
	ll ans = 0;
	int m_id = st2id[mst];
	for (int i = 1; i <= l; i++) {
		// printf("!%d\n", dp[n][i][m_id]);
		ans = (ans + dp[n][i][m_id]) % mod;
	}
	printf("%lld\n", ans);
}

int main() {
	Solve();
}
