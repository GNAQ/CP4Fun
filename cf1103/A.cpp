#include<bits/stdc++.h>
using namespace std;

int a[100];

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int mina=100, maxa=-100;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			mina = min(mina, a[i]);
			maxa = max(maxa, a[i]);
		}
		cout << (maxa - mina + 1) << endl;
	}
}