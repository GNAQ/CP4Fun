#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int fwt[34][6][132000];
int n, m, q;
int a[132000][6];
int ST[50][6];

int b[10];
int c[10];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int w = 0; char ch = 0;
	while (!isdigit(ch)) w |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (w) x = -x;

}

void upd(int st, int cl, int pos, int val) {
	for (int i = pos; i <= n; i += (i & (-i))) {
		fwt[st][cl][i] += val;
	}
}
int qry(int st, int cl, int pos) {
	int res = 0;
	for (int i = pos; i; i -= (i & (-i))) {
		res += fwt[st][cl][i];
	}
	return res;
}

void upd_i(int i, int val) {
	for (int st = 0; st < (1 << m) - 1; st++) {
		int pos = 1;
		while (ST[st][a[i][pos]]) pos++;
		upd(st, a[i][pos], i, val);
	}
}

bool check(int st, int lp, int rp) {
	for (int i = 1; i <= m; i++) {
		c[i] = qry(st, i, rp) - qry(st, i, lp - 1);
		if (c[i] > b[i]) return false;
	}
	// cout << "check: " << st << " " << lp << " " << rp << endl;
	// cout << "C: " << endl;
	// for (int i = 1; i <= m; i++) {
	// 	printf("%d%c", c[i], " \n"[i == m]);
	// }
	return true;
}

// b[i] 是余量
void solve_ans() {
	int st = 0, pos = 1;
	
	for (int i = 1; i <= m; i++) {
		st |= ((b[i] == 0) << (i - 1));
	}
	for (;;) {
		if ((pos > n) || (st == (1 << m) - 1)) break;
		// 二分下一次满课的人位
		// cout << "checking: " << st << " " << pos << " " << n << endl;
		int L = pos, R = n;
		int mans = -1;
		while (L <= R) {
			int mid = (L + R) >> 1;
			if (check(st, pos, mid)) {
				mans = mid;
				L = mid + 1;
			} else {
				R = mid - 1;
			}
		}
		// cout << "L R: " << L << " " << R << endl;
		// cout << "mans: " << mans << endl;
		// mans 不可能等于 -1, 更新 c[i]
		assert(mans != -1);
		check(st, pos, mans);
		for (int i = 1; i <= m; i++) {
			b[i] -= c[i];
			st |= ((b[i] == 0) << (i - 1));
		}
		pos = mans + 1;
		if ((pos > n) || (st == (1 << m) - 1)) break;
	}
	for (int i = 1; i <= m; i++) {
		printf("%d%c", b[i], " \n"[i == m]);
	}
	// puts("\n\n\n");
}

void Solve() {
	readx(n); readx(m); readx(q);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			readx(a[i][j]);
		}
	}
	
	for (int st = 0; st < (1 << m) - 1; st++) {
		for (int i = 1; i <= m; i++) 
			ST[st][i] = (st >> (i - 1)) & 1;
	}
	// init fwt
	for (int i = 1; i <= n; i++) {
		upd_i(i, 1);
	}
	
	int op, x;
	while (q--) {
		readx(op);
		if (op == 1) {
			readx(x);
			// cancel old
			upd_i(x, -1);
			// read new
			for (int j = 1; j <= m; j++) {
				readx(a[x][j]);
			}
			upd_i(x, 1);
		}
		if (op == 2) {
			for (int i = 1; i <= m; i++) {
				readx(b[i]);
			}
			solve_ans();
		}
	}
}

int main() {
	Solve();
}