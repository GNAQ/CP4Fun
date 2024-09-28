#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n;
set<int> edge[500010];
int fa[500010], dep[500010];
int is_leaf[500010];

int q[500010], l, r;

void DFS(int u) {
    is_leaf[u] = 1;
    for (int v : edge[u]) {
        if (v == fa[u]) continue;
        is_leaf[u] = 0;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        DFS(v);
    }
}


void Solve() {
	scanf("%d", &n);
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].insert(v);
        edge[v].insert(u);
    }
    dep[1] = 1;
    DFS(1);
    
    int ans = n + 2;
    int tot = n - 1;
    int cut = 0;
    l = 1, r = 1;
    q[l] = 1;
    while (l <= r) {
        // printf("deter: %d, ans = %d\n\tcut = %d, tot = %d\n", dep[q[l]], tot + cut, cut, tot);
        ans = min(ans, tot + cut);
        int end = r;
        for (int i = l; i <= end; i++) {
            u = q[i];
            for (int v : edge[u]) {
                if (v == fa[u]) continue;
                r++;
                q[r] = v;
                tot--;
            }
        }
        for (int i = l; i <= end; i++) {
            if (is_leaf[q[i]]) {
                int u = q[i];
                while (edge[u].size() == 1 && u != 1) {
                    // printf("cuted %d\n", u);
                    cut++;
                    edge[fa[u]].erase(u);
                    u = fa[u];
                }
            }
        }
        l = end + 1;
    }
    printf("%d\n", ans);
}

void Clear() {
	for (int i = 0; i <= n + 2; i++) {
        edge[i].clear();
        fa[i] = dep[i] = is_leaf[i] = q[i] = 0;
    }
    
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		Solve();
		Clear();
	}
}

/*
E. 做 BFS，每次不是处理队首，而是处理同深度的整个前缀。
统计一下从未入队的点的个数，和已经出队的叶子所在单链的长度即可。
*/