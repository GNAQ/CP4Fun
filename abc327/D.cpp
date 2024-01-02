#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
int a[200010];
vector<int> edge[200010];
int col[200010];
bool ans = true;

void DFS(int u) {
	for (int v : edge[u]) {
		if (col[v] != -1) {
			if (col[v] == col[u]) {
				ans = false;
				return;
			}
			else {
				continue;
			}
		}
		if (!ans) {
			return;
		}
		
		col[v] = col[u] ^ 1;
		DFS(v);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &a[i]);
	}
	int b;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &b);
		edge[a[i]].push_back(b);
		edge[b].push_back(a[i]);
	}
	
	for (int i = 1; i <= n; i++) {
		col[i] = -1;
	}
	for (int i = 1; i <= n; i++) {
		if (col[i] == -1) {
			col[i] = 0;
			DFS(i);
		}
	}
	
	printf("%s\n", ans ? "Yes" : "No");
}


/*
	Solution:
	把 x[i] 当成图的点，每个 x[i] ^ x[j] = 1 的约束是一条边，是个黑白染色。
*/