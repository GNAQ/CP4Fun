输入：一个无向图 $G$，以 $E = \{(u_i, v_i, w_i) | 1 \leqslant i \leqslant M\}$ 表示，$w_i$ 是正整数，且 $G$ 联通。同时输入 $G$ 的一个任意生成树 $E_t = \{(u_t, v_t, w_t) | t \in T\}$

求：一个 $G$ 的割集 $E_c$，满足：$|E_c \cap E_t| = 2$，在这样的 $E_c$ 中，求 $\sum w_c, w_c \in E_c$ 最小的一个 $E_c$，输出 $\sum w_c$ 的值即可。

割 $(S, T, E_c)$ 的定义：$S \subset V$, $T=V-S$。$\forall (ui, vi, wi) \in E$, $E_c = \{ (u, v, w) | (u \in S \land v \in T) \lor (u \in T \land v \in S)\}$。$(S T)$ 称为割，$E_c$ 称为割集

输入保证至少存在一个满足要求的答案。输入的数据都是 $3 \sim 3e5$ 之内的正整数。时限 3s。

----

Solution:

考虑交集为 1 而不是 2 的时候题目怎么做。游走这个生成树的时候，维护跨越当前父边的非树边的边权和，对于切断当前父边对应的割，父边权值加上这个被维护的值就是答案，在所有这样的答案里面取个最小即可。实际上可以离线地将 u <-> lca 和 lca <-> v 的链上都 +w，这个过程用离线 LCA + 树上差分做是线性的。

考虑交集为 2，是要最小化 $W_s(b) + W_s(c) - W(b, c)$, 其中 $W_s(x)$ 是交集为 1 的版本下，断 $(x, \mathrm{fa}_x)$ 这条边的答案。$W(b, c)$ 是 $u \in \mathrm{subtree}(b), v \in \mathrm{subtree}(c)$ 的所有 $(u, v, w)$ 的 $\sum w$。

不妨设 lca(b, c) 和 b, c 都不相同，也就是 b, c 不共链。考虑枚举 b 并用什么数据结构维护 Ws(c) - W(b, c)，用 DFS 序枚举 b，然后考虑除了 b 之外的所有与 b 不共链的点（记为\*），那么每条边会被先加入到 W(b, \*) 的考虑范围之中，再被除掉（需要这条边的两点不同时在 subtree(b) 内），恰好一进一出。加入是 b = LCA(u, v) 的时候边 (u, v, w) 会被加入 set W(b, \*)，踢出就是 dfsorder(b) > min(dfsorder(u), dfsord(v))。不妨设 u ∈ subtree(b), v ∈ subtree(*)，dfsord(u) < dfsord(v)。那么实际上考虑一堆集合 set W(b, \*) 之中，有哪些是真正会出现 (u, v, w) 的集合：是当且仅当 \* 取 { lca(u, v) ... v }，这是个区间操作，用树链剖分维护这个东西就行了。

如果 b, c 共链，用相同的思想推一遍这个做法就可以。会有一些维护细节上的不一样。