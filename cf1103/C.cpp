#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	int t; 
	cin >> t;
	while (t--) {
		ll a, b, x;
		cin >> a >> b >> x;
		ll minans = abs(a - b);
		int curstep = 0;
		while (max(a, b) > 0) {
			if (a < b) { swap(a, b); }
			a = a / x;
			curstep++;
			minans = min<ll>(minans, curstep + abs(a - b));
			if (a == b) {
				break;
			}
		}
		cout << minans << endl;
	}
}