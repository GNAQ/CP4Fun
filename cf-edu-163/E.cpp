#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, k;
int a[100], c[100];

void Solve() {
	scanf("%d%d", &n, &k);
	// calculate t
	int t;
	for (int i = n; i >= 1; i--) {
		int cost = (i - 1) + 1;
		if (cost <= k) {
			t = i;
			break;
		}
	}
	int q = n / t + (n % t != 0);
	for (int i = 1; i <= n; i += t) {
		for (int j = i; j < i + t && j <= n; j++) {
			int tt = min(t, n - i + 1);
			
			c[j] = (i - 1) / t + 1;
			
			if (j - i + 1 <= (tt + 1) / 2) {
				a[j] = (i + (tt + 1) / 2 - 1) - (j - i);
			} else {
				a[j] = (i + tt - 1) - (j - (i + (tt + 1) / 2));
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("%d\n", q);
	for (int i = 1; i <= n; i++) {
		printf("%d ", c[i]);
	}
	printf("\n");
}

void Clear() {
	memset(a, 0, sizeof(a));
	memset(c, 0, sizeof(c));
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		Solve();
		Clear();
	}
}

/*
Solution:
	考虑每个 Clique 的 ai 都是和它们的 i 内部消化的，反之，则两个 clique 之间交换 ai，这会使得两个 clique 内的边权不变或变大，不优。
	在这种情况下，每个 clique 内的边权是基于它的相对大小的，故 clique 的划分一定是均分，既有 n / t 个 t 大小的 clique（带一个余数）
	每个 clique 内部的点看作一个二维平面的点 (i, ai)，那么各点之间的边权就是它们的曼哈顿距离
	我们要使得每个 clique 内部的边权和最小，那么就是求每个 clique 内部的点的曼哈顿距离最大值最小
	这个东西存在一个确定性的贪心构造，就是 (1, t / 2), (2, t / 2 - 1), ... , (t / 2, 1) 和 (t / 2 + 1, t), (t / 2 + 2, t - 1), ... , (t, t / 2 + 1)
*/