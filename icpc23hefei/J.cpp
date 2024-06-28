#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m;
struct edge {
	int u, v, w;
} e[1000005];

int ms[300005], mt[300005];
set<int> grp[300005];
int dsu[300005];

template<typename int_t>
void readx(int_t &x) {
	x = 0; int w = 0; char ch = 0;
	while (!isdigit(ch)) w |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (w) x = -x;

}

int getfa(int x) {
	return dsu[x] == x ? x : dsu[x] = getfa(dsu[x]);
}
void merge(int x, int y) {
	x = getfa(x); y = getfa(y);
	if (x != y) {
		int sx = grp[x].size(), sy = grp[y].size();
		if (sx < sy) {
			swap(x, y);
			swap(sx, sy);
		}
		dsu[y] = x;
		for (int i : grp[y]) {
			grp[x].insert(i);
		}
		grp[y].clear();
	}
}

void Solve() {
	readx(n); readx(m);
	// special case
	int ans1 = INT32_MAX;
	for (int i = 1; i <= m; i++) {
		readx(e[i].u); readx(e[i].v); readx(e[i].w);
		if (min(e[i].u, e[i].v) == 1 && max(e[i].u, e[i].v) == n) {
			ans1 = min(ans1, e[i].w);
		}
	}
	
	// init
	sort(e + 1, e + m + 1, [](edge a, edge b) {
		return a.w < b.w;
	});
	for (int i = 1; i <= n; i++) {
		dsu[i] = i;
		grp[i].insert(i);
		ms[i] = mt[i] = -1;
	}
	ms[1] = 0; mt[n] = 0;
	int ans2 = INT32_MAX;
	
	for (int i = 1; i <= m; i++) {
		if (ms[e[i].u] != -1 && mt[e[i].v] != -1) {
			ans2 = min(ans2, e[i].w + max(ms[e[i].u], mt[e[i].v]));
		}
		if (ms[e[i].v] != -1 && mt[e[i].u] != -1) {
			ans2 = min(ans2, e[i].w + max(ms[e[i].v], mt[e[i].u]));
		}
		
		if (getfa(e[i].u) != getfa(e[i].v)) {
			if (getfa(1) == getfa(e[i].u)) {
				set<int> &g = grp[getfa(e[i].v)];
				for (int j : g) {
					assert(ms[j] == -1);
					ms[j] = e[i].w;
				}
			}
			if (getfa(1) == getfa(e[i].v)) {
				set<int> &g = grp[getfa(e[i].u)];
				for (int j : g) {
					assert(ms[j] == -1);
					ms[j] = e[i].w;
				}
			}
			if (getfa(n) == getfa(e[i].u)) {
				set<int> &g = grp[getfa(e[i].v)];
				for (int j : g) {
					assert(mt[j] == -1);
					mt[j] = e[i].w;
				}
			}
			if (getfa(n) == getfa(e[i].v)) {
				set<int> &g = grp[getfa(e[i].u)];
				for (int j : g) {
					assert(mt[j] == -1);
					mt[j] = e[i].w;
				}
			}
			
			merge(e[i].u, e[i].v);
		}
	}
	
	printf("%d\n", min(ans1, ans2));
}

int main() {
	Solve();
}
