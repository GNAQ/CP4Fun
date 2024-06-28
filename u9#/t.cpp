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
