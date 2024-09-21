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


/*
Solution:
  有个傻逼想出对的 DP 之后一直觉得这玩意是 O(n^4) 的。
  这就是不写明白转移方程，只大概拍拍脑子的后果。
  
  考虑 Dilworth 定理。实际上在一个序列上，这个定理的形式完全可以被强化：
    一个序列的不降子序列的最小的划分数目，等于这个序列的反向序列的最长上升子序列长度。
  那么我们考虑计数 B 序列的翻转序列。约束条件就变成待计数序列的最长上升子序列长度不超过 2。
  
  考虑从小到达加入每个数。加入 a[i] 个 i 的时候，它所有合法的插入位置都在当前序列的前面。
  也就是说，插入 i 之前，我们可以设当前序列，左起第一个长度为 2 的上升子序列的位置是 (j, j+1)。
  这个时候当前序列的长相一定是 [1 ... j] 全不增，[j+1] 是那个上升的拐点。
  那么我们插入 a[i] 个 i，显然就是往最头上插入 x 个 i，
  然后往先前序列的 [1 ... j] 里面插入 (a[i] - x) 个 i。
  
  考虑 dp[i][j] 表示插入了前 i 个数，序列拐点在 j 这个地方（也就是 [1 ... j] 单调不增）
  那么从 dp[i-1][j] --> dp[i][k]，考虑枚举 x，则需要额外拿出原先的 [1 ... t] 补足 k 长度的前缀。
  这里 t = k - x。此后我们手动往原先的 (t, t+1) 之间插入 1 个 a[i] 创造新的拐点（如果 t = j 也可以不插入）
  然后我们在 (j - t) + (a[i] - x - 1) 个候选位置里选 (j - t) 个位置放置 [t+1 ... j]，剩下的放 i。
*/