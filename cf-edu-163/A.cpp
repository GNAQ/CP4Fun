#include <bits/stdc++.h>
using namespace std;

int n;

void Solve() {
	scanf("%d", &n);
	if (n % 2) {
		puts("NO");
		return;
	}
	puts("YES");
	for (int i = 1; i <= (n / 4); i++) {
		printf("AABB");
	}
	if (n % 4) {
		printf("AA");
	}
	puts("");
	return;
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
Solution:
	考虑到向开头和结尾插入 #
	考虑每次向一个左右均非 A，也就是不是 A|A 的构型里面，插入一个 AAA...AAA 这样的子串，贡献只会是 2.
	又观察到 n = 3 的时候构造不出来答案，n = 2 的时候可以是 AA、BB 这样
	所以 n 奇数无解，偶数就是 (AABB) * (n / 4) + (AA) * (n % 4)
*/