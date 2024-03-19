#include <bits/stdc++.h>
using namespace std;

int n;
int a[100];

void Solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	bool ans = true;
	vector<int> b;
	b.push_back(a[n]);
	for (int i = n - 1; i >= 1; i--) {
		if (a[i] > b[b.size() - 1]) {
			if (a[i] <= 9) {
				ans = false;
			} else if ((a[i] % 10 < a[i] / 10) || (a[i] % 10 > b[b.size() - 1])) {
				ans = false;
			} else {
				b.push_back(a[i] % 10);
				b.push_back(a[i] / 10);
			}
		} else {
			b.push_back(a[i]);
		}
	}
	if (ans) {
		puts("YES");
	} else {
		puts("NO");
	}
}

void Clear() {
	
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		Solve();
		Clear();
	}
}

/*
Solution
	观察到这是个骗子题，因为 ai <= 99，所以从后往前贪心地拆就行了
	如果 ai 数位再多些，需要考虑拆分的时候再套一层贪心，倒着拆的时候把最左侧的数拆的大一些。
*/