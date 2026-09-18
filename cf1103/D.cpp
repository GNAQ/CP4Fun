#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	int t; 
	cin >> t;
	while (t--) {
		int n, k;
		vector<int> a;
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			int tmp;
			cin >> tmp;
			a.push_back(tmp);
		}
		if (n == 1) {
			cout << "NO" << endl;
			continue;
		}
		sort(a.begin(), a.end());
		bool flag = false;
		int r = a.size() - 1;
		for (int i = a.size() - 1; i >= 0;) {
			while (i > 0 && a[i - 1] == a[r])
				i--;
			int max_cnt = r - i + 1;
			if (max_cnt % 2 == 0) {
				flag = true;
				break;
			}
			else if (i > 0 && (a[i] - a[i - 1] <= k)) {
				flag = true;
				break;
			}
			r = i - 1;
			i = i - 1;
		}
		cout << (flag ? "YES" : "NO") << endl;
	}
}