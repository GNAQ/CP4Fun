#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int mod = 998244353;
int dp[1005][1005], a[1005], n, m;

int C[1005][1005], sumC[1005][1005];

void init_c() {
    C[0][0] = 1;
    for (int i = 1; i <= 501; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
        }
    }
    for (int i = 0; i <= 501; i++) {
        sumC[i][0] = C[i][0];
        for (int j = 1; j <= i + 2; j++) {
            sumC[i][j] = (sumC[i][j - 1] + C[i][j]) % mod;
        }
    }
}

int sum_c(int _n, int _m1, int _m2) {
    if (_m1 == 0) {
        return sumC[_n][_m2];
    }
    return ((sumC[_n][_m2] - sumC[_n][_m1 - 1]) % mod + mod) % mod; 
}

void Solve() {
	scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    int sum = 0;
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        sum += a[i];
        // cout << "!!" << "i = " << i << endl;
        for (int k = 0; k <= sum; k++) {
            // dp[i-1][j] 至少出一个元素作为 t 段插入到一堆 a[i] 中间
            for (int j = 1; j <= sum - a[i]; j++) {
                int tl = max(1, k - a[i]), tr = min(k, j);
                int cl = j - tr, cr = j - tl;
                int base = j + a[i] - k - 1;
                // printf("k=%d, j=%d, ai=%d, (tl, tr) = (%d, %d), (cl, cr) = (%d, %d), base=%d\n", k, j, a[i], tl, tr, cl, cr, base);
                if (tl > tr or base < 0)
                    continue;
                
                // printf("dp[i][%d] += (dp[i-1][%d]=%d) * %d\n", k, j, dp[i-1][j], sum_c(base, cl, cr));
                dp[i][k] = (dp[i][k] + (1ll * dp[i - 1][j] * sum_c(base, cl, cr) % mod)) % mod;
            }
            // 全放到前面，实际上 j==0 只能在这转移。
            if (k >= a[i])
                dp[i][k] = (dp[i][k] + dp[i - 1][k - a[i]]) % mod;
        }
        // cout << "dp = " << endl;
        // for (int j = 0; j <= sum; j++) {
        //     printf("%d ", dp[i][j]);
        // }
        // cout << endl << endl;
    }
    ll ans = 0;
    for (int i = 0; i <= sum; i++) {
        ans = (ans + dp[n][i]) % mod;
    }
    printf("%lld\n", ans);
}


int main() {
    init_c();
    Solve();
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
  (j - t) + (a[i] - x - 1) == j + a[i] - k - 1
  
  最后转移就是 dp[i][k] += (dp[i-1][j] * C(j+a[i]-k-1 , j-t)), t = [max(0, k-a[i]) ... min(k, j)]
*/