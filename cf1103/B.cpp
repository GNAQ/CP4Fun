#include<bits/stdc++.h>
using namespace std;


int main() {
	string s;
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		cin >> s;
		for (int i = 0; i < n - k; i++) {
			if (s[i] == '1') {
				s[i] = '0';
				s[i + k] = ((s[i + k] == '0') ? '1' : '0');
			}
		}
		// check
		bool ok = true;
		for (int i = 0; i < n; i++) {
			ok = ok & (s[i] == '0');
		}
		cout << (ok ? "yes" : "no") << endl;
	}
}