#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

int n;
char mp[5][200010];
bool vis[5][200010];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void Solve() {
	scanf("%d", &n);
	for (int i = 1; i <= 2; i++) {
		scanf("%s", mp[i] + 1);
	}
	
	queue<pair<int, int>> q;
	q.push({1, 1});
	vis[1][1] = true;
	while (q.size()) {
		// auto [x, y] = q.front(); 
		auto x = q.front().first;
		auto y = q.front().second;
		q.pop();
		if (x == 2 && y == n) {
			puts("YES");
			return;
		}
		for (int w = 0; w < 4; w++) {
			int nx = x + dx[w];
			int ny = y + dy[w];
			if (nx < 1 || nx > 2 || ny < 1 || ny > n) {
				continue;
			}
			if (mp[nx][ny] == '<') {
				ny--;
			} else if (mp[nx][ny] == '>') {
				ny++;
			}
			if (vis[nx][ny])
				continue;
			vis[nx][ny] = true;
			q.push({nx, ny});
		}
	
	}
	puts("NO");
	
}

void Clear() {
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= n + 2; j++) {
			mp[i][j] = 0;
			vis[i][j] = false;
		}
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
Solution
	矫情题，BFS 就做完了
*/