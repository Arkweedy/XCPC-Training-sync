缩点后得到一个边双树，连边的点集之间恰好有一条连边
两个点集连一条边(有$2^{sz[u] \cdot sz[v]} - 1 $种连法)，可以覆盖路径上的所有边
要求算出覆盖所有边的方法有多少种
考虑做一个$O(n^2)$的容斥

边可以转移到较深的点？
怎么处理两个子树之间的点连边的情况？ -- 合并点集
我们是钦定一些子树不能被合并，于是候选点集的sz总和是可以维护的
先合并完所有子树，最后加上钦定自身？
$dp[p][c]$表示只考虑$p$子树内连边，还有$c$条边没有覆盖的方案数？


<!-- 推一下转移：
$$\begin{align*}
ndp_{p, c} &= \sum_i\sum_{U = P_i \times S_{m - i}} c_{p, i}  c_{s,m - i}  2^{sz_{p, i} * sz_{s, m - i} - 1}\\
&= \sum_i\sum_{U = P_i \times S_{m - i}} c_{p, i} * c_{s,m - i} * sz_{p, i} * sz_{s, m - i} - \sum_{U = P_i \times S_{m - i}} c_{p, i} * c_{s,m - i}\\
&= \sum_i(\sum_{P_i} c_{p, i} * sz_{p, i}) * (\sum_{S_{m - i}}c_{s, m - i} sz_{s, m - i}) - ...
\end{align*}$$
于是需要维护两个量(子树确定$c$条边不选后所有状态的和)
1. 方案数(dp)
2. 方案数 * 可连边sz

$dpsz[p][c]$ .... 这些方案中，可以连边的sz*cnt总和

$$\begin{align*}
ndp_{p, c} &= \sum_i\sum_{U = P_i \times S_{m - i}} c_{p, i} * c_{s,m - i} * (sz_{p, i} * sz_{s, m - i} - 1)\\
&= \sum_i\sum_{U = P_i \times S_{m - i}} c_{p, i} * c_{s,m - i} * sz_{p, i} * sz_{s, m - i} - \sum_{U = P_i \times S_{m - i}} c_{p, i} * c_{s,m - i}\\
&= \sum_i(\sum_{P_i} c_{p, i} * sz_{p, i}) * (\sum_{S_{m - i}}c_{s, m - i} sz_{s, m - i}) - ...
\end{align*}$$ -->
如果是精确不覆盖c条，似乎在转移上有困难。
于是可以用一个钦定k条不覆盖，其他的随意来容斥

$f(c), g(c)$
$f(k) = \sum_{i = k}^n \binom{i}{k} g(i)$
于是有
$g(0) = \sum_{k = 0}^n (-1)^k \binom{k}{0} f(k) = \sum_{k = 0}^n (-1)^k f(k)$

$f$似乎不好直接dp得出来，因为我们需要知道钦定断的边数/当前连通块大小 两个量才能维护转移
然而我们算答案只需要$(-1)^kf(k)$的总和
而$(-1)^kf(k)$的总和是可以通过dp得出来的，因为转移的额外系数只和连通块大小有关，和钦定的边数无关,我们可以按连通块大小对dp值分类
定义$dp_{p, sz} = \sum_k (-1)^k f_{p, sz}(k)$
其中$f_{p, sz}$是以$p$为根的子树，考虑大小为$sz$的连通块的$f$
(这个说法可能不太严谨，准确来说是通过钦定断边后，还有$sz$个点可以自由连边)
我们只需要树形dp转移时枚举每条边断/不断，如果断，那么就乘上-1转移，如果不断，就合并连通块，dp转移如下：
$$
ndp_{p, i + j} \leftarrow dp_{p, i}\cdot dp_{s, j} \cdot 2^{ij - 1} \\
ndp_{p, i} \leftarrow -dp_{p, i} \cdot dp_{s, j}
$$
最后的答案为
$$ans = \sum_{i = 0}^n dp_{root, i}$$