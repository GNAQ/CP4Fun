#include <bits/stdc++.h>
typedef long long ll;
using namespace std;


template<typename int_t>
void readx(int_t &x) {
	x = 0; int w = 0; char ch = 0;
	while (!isdigit(ch)) w |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	if (w) x = -x;

}


void Solve() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	map<string, int> cnt;
	int maxv;
	string ans;
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		cnt[s]++;
		if (cnt[s] > maxv) {
			maxv = cnt[s];
			ans = s;
		}
	}
	if (maxv > n / 2) {
		cout << ans << endl;
	} else {
		cout << "uh-oh" << endl;
	}
}

void Clear() {
	
}

int main() {
	// int T; scanf("%d", &T);
	// while (T--) {
		Solve();
		// Clear();
	// }
}
