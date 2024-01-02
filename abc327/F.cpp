#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define LCH (u << 1)
#define RCH (u << 1 | 1)

struct SegTree {
	int l, r;
	int val, tag;
} seg[800005];
int ql, qr, qv;

int n, d, w;
pair<int, int> p[200010];

void BuildTree(int lx, int rx, int u) {
	seg[u].l = lx, seg[u].r = rx;
	seg[u].val = 0; seg[u].tag = 0;
	if (lx == rx) return;
	int mid = (lx + rx) >> 1;
	BuildTree(lx, mid, LCH);
	BuildTree(mid + 1, rx, RCH);
}

void Pushdown(int u) {
	if (seg[u].tag == 0)
		return;
	int t = seg[u].tag;
	seg[u].tag = 0;
	
	seg[LCH].val += t;
	seg[LCH].tag += t;
	seg[RCH].val += t;
	seg[RCH].tag += t;
}

void UpdRng(int u) {
	if (seg[u].l >= ql && seg[u].r <= qr) {
		seg[u].val += qv;
		seg[u].tag += qv;
		return;
	}
	Pushdown(u);
	int mid = (seg[u].l + seg[u].r) / 2;
	if (ql <= mid) 
		UpdRng(LCH);
	if (qr > mid) 
		UpdRng(RCH);
	seg[u].val = max(seg[LCH].val, seg[RCH].val);
}

int QryP(int u) {
	return seg[1].val;
}

int main() {
	scanf("%d%d%d", &n, &d, &w);
	int lim_x = 0;
	for (int i = 1; i <= n; i++) {
		// second is x, first is y, weird
		scanf("%d%d", &p[i].first, &p[i].second);
		lim_x = max(lim_x, p[i].second);
	}
	
	sort(p + 1, p + n + 1, 
		[](pair<int, int> &a, pair<int, int> &b){
			return a.first < b.first;
		});
	
	BuildTree(1, lim_x, 1);
	
	int ans = 0;
	int del_ptr = 1;
	for (int i = 1; i <= n; i++) {
		int ny = p[i].first, nx = p[i].second;
		
		while (del_ptr < i) {
			if (ny - p[del_ptr].first >= d) {
				// delete point [del_ptr]
				ql = max(p[del_ptr].second - w + 1, 1), qr = p[del_ptr].second;
				qv = -1;
				UpdRng(1);
				del_ptr++;
			} else {
				break;
			}
		}
		
		// add new point and update answer
		ql = max(nx - w + 1, 1), qr = nx;
		qv = 1;
		UpdRng(1);
		
		ans = max(ans, QryP(1));
	}
	
	printf("%d\n", ans);
	return 0;
}

/*
	Solution:
	注意到每个点以两维一个 pair 表示，并且确保 pair 两两不同，容易想到将其当作二维坐标点。
	那题目要求的就是用一个固定长宽的框，框出最多的点。这是一个经典的裸的二维数点问题。
	我们考虑用数据结构维护。将所有的点按照 y 轴坐标排序。
	对 y 轴做扫描线，将扫到的点加入数据结构，并将所有距离扫描线当前坐标远于 d 的点删除。
	这样，我们就满足了 y 轴的框选条件。现在就是在数据结构维护的 x 轴上框出点最多的区域。
	反过来想，考虑将 1 ... lim_x 作为 x 轴框的左侧起点，这样形成的答案数组，
	那么一个点 p[x] 能向其中 p[x] - l + 1, p[x] 这些下标都提供 1 的贡献。
	于是用一个能维护序列的数据结构，按这样的道理维护答案数组即可。
*/