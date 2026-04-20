**思路**

题目等价于：在 `1 <= q < MOD` 中，最小化

```text
f(q) = q + (q x mod MOD)
```

因为一旦选了 `q`，最优的 `p` 就只能是 `p = qx mod MOD`。

我在 [I.cpp:22](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L22) 到 [I.cpp:58](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L58) 里做的事，是不直接一个个枚举 `q`，而是维护两组“同余解”：

- 正解 `A = (qa, pa)`，满足 `pa > 0` 且 `pa ≡ qa x (mod MOD)`
- 负解 `B = (qb, pb)`，满足 `pb < 0` 且 `pb ≡ qb x (mod MOD)`

初始化就是

- `A = (1, x)`
- `B = (1, x - MOD)`

对应代码见 [I.cpp:22](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L22) 到 [I.cpp:25](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L25)。

---

这两个状态一直满足一个很关键的不变量：

```text
pa * qb - pb * qa = MOD
```

初始时显然成立：

```text
x * 1 - (x - MOD) * 1 = MOD
```

而两种更新：

- `B <- B + tA`
- `A <- A + tB`

都不会改变这个行列式值，所以它始终成立。

把 `a = pa > 0`，`b = -pb > 0` 代进去，上式变成：

```text
a * qb + b * qa = MOD
```

这说明 `A` 和 `B` 是夹在 0 两侧的一对“相邻边界”。

---

接下来为什么能“整段跳过”？

先看 `B + tA`：

```text
q = qb + t qa
signed_p = pb + t pa = -b + t a
```

当 `signed_p < 0` 时，它对应的真实模意义下的 `p` 是 `MOD + signed_p`，这整段都还不是我们要的正解边界。  
而最后一个仍然为负的 `t` 正是

```text
t = floor((b - 1) / a)
```

这就是代码里的 [I.cpp:39](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L39) 到 [I.cpp:47](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L47)。

同理，看 `A + tB`：

```text
q = qa + t qb
p = pa + t pb = a - t b
```

只要它还保持 `p > 0`，就是一整段合法候选。  
这一段里的 `p+q` 是关于 `t` 的一次函数，所以最优值只可能出现在端点，不可能在中间。  
因此可以直接跳到“最后一个仍然合法的端点”：

```text
t = floor((a - 1) / b)
```

这就是 [I.cpp:49](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L49) 到 [I.cpp:56](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L56)。

循环开始时我总会先用当前正解 `A` 更新答案，见 [I.cpp:27](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L27) 到 [I.cpp:33](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L33)，所以每一段里该看的端点都不会漏。

---

**为什么这其实就是欧几里得算法**

令

```text
a = pa > 0
b = -pb > 0
```

那么两种转移就是：

- 若 `a <= b`，则 `b <- b - t a`，其中 `t = floor((b - 1)/a)`
- 若 `a > b`，则 `a <- a - t b`，其中 `t = floor((a - 1)/b)`

也就是说，每次都把较大的那个数减去若干个较小的那个数，直到它刚好还保持正。  
这和欧几里得算法按整商批量做减法是同一个过程，本质上就是“带整商跳跃的辗转相除”。

终止条件 [I.cpp:35](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L35) 到 [I.cpp:36](d:/XCPC_Training/Others/Contests/WhalicaRound2/I.cpp#L36) 的 `pa = 1, pb = -1`，对应的就是这套过程已经缩到最小边界，再也不可能产生新的更优端点了。

---

**时间复杂度**

每次循环都相当于欧几里得算法的一步“整商跳跃”，把 `a, b` 中较大的那个降到严格小于较小的那个。

所以：

- 初始时 `1 <= a, b < MOD`
- 每轮都是一次 Euclid step
- 总轮数和欧几里得算法相同，为 `O(log MOD)`

由于这里 `MOD = 998244353` 是常数，单组实际上就是很小的常数次循环；严格写法仍然是：

```text
时间复杂度：O(log MOD)
空间复杂度：O(1)
```

如果你愿意，我也可以继续把这份证明整理成更像比赛题解的写法，直接适合贴到注释或题解文档里。