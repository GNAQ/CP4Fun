#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod1 = 1e9 + 9, mod2 = 993244853;
const ll w1 = 233, w2 = 19260817;
int n;
char ss[10010];

ll fastpow(ll a, ll b, ll mod) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

void Solve() {
	scanf("%s", ss + 1);
	n = strlen(ss + 1);
	int ans = 0;
	
	for (int len = n / 2; len >= 1; len--) {
		for (int rt = n; rt >= 2 * len; rt--) {
			int lt = rt - len;
			bool flag = 1;
			
			for (int j = rt; j > lt; j--) {
				int i = j - len;
				if (ss[i] != '?' && ss[j] != '?' && ss[i] != ss[j]) {
					flag = 0;
					rt = j - 1;
					rt++; // cancel rt-- in the for loop
					break;
				} else if (ss[i] == '?' || ss[j] == '?') {
					continue;
				} else if (ss[i] == ss[j]) {
					continue;
				}
			}
			if (flag) {
				printf("%d\n", len * 2);
				return;
			} else {
				;
			}
		}
	}
	puts("0");
	return;
}

void Clear() {
	for (int i = 0; i <= n + 2; i++) {
		ss[i] = 0;
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
Solution:
	由于通配符的存在，KMP 和 HASH 都不太好使，我们不妨考虑一下别的枚举均摊方法或 DP 方法。
	考虑答案空间的大小是 O(n^2) 的，因为考虑每个答案可以被唯一地表示为 (ls, lt)，也就是左侧串的首尾，或者说 (lt, rt)。这两种方式是等价的。
	不妨从大到小枚举答案长度，此后倒着枚举 rt，算出 lt。暴力地从 后 向前对前后串进行匹配。
	如果在位置 (i, j) 上 fail 了，那么代表着 ans = len 的 O(n) 大小的解空间里面，下一个可能的答案应该找 (lt = i - 1, rt = j - 1)
	这样复杂度就是均摊的——每层 len 用 O(n) 的时间搞定
*/