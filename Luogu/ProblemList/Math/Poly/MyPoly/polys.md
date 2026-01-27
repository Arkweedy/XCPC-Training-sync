# 多项式全家桶
整理各种多项式函数
## 快速傅里叶变换 fft

## 快速数论变换 ntt
### 离散傅里叶变换 `dft(poly& f)`
类似fft，需要在 $\mathbb{F}_P$下找到合适的$n$次单位根$w_n$
根据数论知识，$n$次单位根存在当且仅当 $n \mid \phi(P)$, 即 $n | (P - 1)$
而由于我们需要做蝶形变换，因此 $n$ 是 $2$ 的高次幂，因此我们希望 $P$ 可以写成 ：
$$P = q\cdot 2^k + 1$$
这样的形式，且$k$尽可能大，以方便我们可以对更长的数组做ntt.
$998244353$是一个合适的数， 其中一个原根 $g = 3$
知道原根后，$n$次单位根$\omega_n$是易求的：
$$\omega_n = g^{\frac{P - 1}{n}}$$
式子右边很容易验证符合 $w_n$ 的性质.
离散傅里叶变换公式：
$$F_k = f(\omega^k) = \sum_{j = 0}^{n - 1} w^{jk}f_j $$
于是仿照fft做蝶形变换即可

### 离散傅里叶逆变换 `idft(poly& f)`
ntt实现的idft可以使用一点技巧
fft中，实现逆变换是使用$\omega_{n}^{-1}$,这里也可以这么做，不过也可以利用数论知识换一下形式:
$$\begin{align*}
f_k = F(\omega^{-k}) &= \sum_{j = 0}^{n - 1} w^{-jk}F_j \\
&= \sum_{j = 0}^{n - 1} w^{(n-j)k}F_j \\
&= \sum_{j = 0}^{n - 1} w^{jk}F_{n - j \bmod n}
\end{align*}$$
因此我们可以对于$j \in [1, n - 1]$, 我们翻转这一段，而$n - 0 = 0 \pmod n$，不变，然后做一次dft.
于是写出来一个很像 1-base 但是完全不是这么回事的代码：
```c++
void idft(vector<int>& f)
{
    int n = f.size();
    int invn = inv(n);
    reverse(f.begin() + 1, f.end());
    dft(f);
    for(int i = 0;i < n;i++){
        f[i] = 1ll * f[i] * invn % P;
    }
    return;
}
```

### 原理
为什么fft可以把卷积变成点积？甚至这一策略可以平移到$\mathbb{F}_P$？
其实可以只关注我们利用到的性质，在最小条件下进行推理。
给定一个交换环$R$， $\omega \in R$, $\operatorname{ord}(\omega) = n$
定义$R^n$上的dft(没有归一化)：
$$\hat{a}(k) = \sum_{j = 0}^{n - 1}a_j w^{jk}, k = 0,1,\dots,n-1$$
定义$R^n$上的**循环**卷积：
$$(a * b)_t = \sum_{j = 0}^{n - 1} a_j b_{t - j \bmod n}$$

于是可以证明：
$$\widehat{a*b} = \hat{a} * \hat{b}$$

给出一个证明：
令$c = a * b$有：
$$\begin{align*}
    \hat{c}_k &= \sum_{j = 0}^{n - 1} c_j w^{jk} \\
    &= \sum_{j = 0}^{n - 1} \sum_{t = 0}^{n - 1} (a_t b_{j - t \bmod n}) w^{jk}\\
    &= \sum_{t = 0} a_t \sum_{j = 0}^{n - 1} b_{j - t \bmod n} w^{jk} \\
    &= \sum_{t = 0} a_t \sum_{s = j - t \bmod n, s = 0}^{n - 1} b_{s} w^{(s + t)k} \\
    &= \sum_{t = 0} a_t w^{tk} \sum_{s = 0}b_{s} w^{sk} \\
    &= \hat{a}_k \hat{b}_k
\end{align*}$$

所以这个策略在 $C$, $\mathbb{F}_P$上均有用
有一个平时注意不到的点是：我们实际上实现的是循环卷积，而非普通卷积，这个性质在一些特殊的场合可以发挥作用。
也就是说，我们实现的多项式乘法不是在$\mathbb{F}_P^n$上，而是在$\mathbb{F}_P[x]/(x^n - 1)$这个商环上。
本质上，dft是商环$R[x]/(x^n - 1)$到直积$R^n$的同构。

## 截断 `truck(int m)`
从第$m$位开始截断，
形式化即$\mod x^m$

## 右移 `shift(int m)`
移位函数，在左边插入若干个$0$，或者截断一些位
形式化即 $x^m f$ 去掉负数项

## 翻转 `rev()`
从最高位开始翻转多项式
形式化来说，相当于$f^R = x^{\operatorname{deg}(f)} f(\frac{1}{x})$

## 形式导数 `deriv()`
求形式导数

## 形式不定积分 `integr()`
求形式积分

## 多项式乘法逆 `inv(int m)`
使用多项式牛顿迭代：
$$\begin{align*}
Af &= 1\\ 
A - \frac{1}{f} &= 0\\
\rightarrow f_{2n} = f_n - \frac{A - f_n^{-1}}{-f_n^{-2}} &= f_n(2 + Af_n)
\end{align*}$$
从$f_0 = A_0^{-1}$开始迭代即可
因此要求常数位非$0$
另外一种解释是可以看作$\mod x^\infty$ 下求逆，那么存在逆元当且仅当$\gcd(f, x^\infty) = 1$,即$f$常数项不为$0$.

## 多项式对数函数 `log(int m)`
$$\begin{align*}
f &= \ln A(x) \\
f'&= \frac{1}{A(x)} \\
f &= \int \frac{1}{A(x)}
\end{align*}$$
求逆再积分回去即可
根据定义，**常数项必须是1**

## 多项式指数函数 `exp(int m)`
有两种方法，$O(n\log n)$ 的牛顿迭代 和 $O(n \log^2 n)$ 的半在线卷积
实际上半在线卷积要比牛顿迭代快不少

### 牛顿迭代
根据初始条件写出迭代式：
$$\begin{align*}
f &= e^{A}\\ 
A - \ln f &= 0\\
\rightarrow f_{2n} = f_n - \frac{A - \ln f_n}{-f_n^{-1}} &= f_n(1 + A - \ln f_n)
\end{align*}$$
从$f_0 = 1$开始迭代即可
根据主定理，时间复杂度为$O(n\log n)$

### 半在线卷积
$$\begin{align*}
F &= e^{G}\\ 
\ln F &= G\\
\frac{F'}{F} &= G'\\
F' &= FG' \\
\rightarrow nf_{n} &= \sum_{k = 0}^{n - 1} kg_k f_{n - k}
\end{align*}$$
(对求导算子对系数的影响要熟练)
用半在线卷积实现即可

## 多项式快速幂 `pow(int n, int k)`
如果常数项为$1$，直接$\ln + \exp$即可处理
常数项非$1$，那么不能直接取对数函数
首先，先去掉前面为$0$的项，相当于提一个因子$x^i$
其次，如果处理后的常数项非$1$，那么再提一个常数因子$v$即可
求解多项式快速幂后，乘上 $v^k$，补上 $ki$ 个 $0$ 即可

在$k$相当大的时候需要注意的一些点：
实际上，可以证明：
$$f(x)^k \equiv f(x)^{k \bmod P} \mod x^P$$
这个可以展开$\exp$系数得到这个结论
然而，在我们上面的处理中，有一步是乘上 $v^k$,显然这里的 $k$ 必须模 $\phi(P) = P - 1$
**注意这两个地方的模数是不一样的！**
此外，我们实际上要补$ki$ 而非 $(k \bmod P)i$ 个 $0$， 所以当 $k \equiv 0 \pmod P$时，要特判一下，避免没有补应该补的 $0$ 导致错误。

## 多项式开根 `sqrt(int m)`
使用多项式牛顿迭代
$$\begin{align*}
f &= \sqrt{A}\\ 
A - f^2 &= 0\\
\rightarrow f_{2n} = f_n - \frac{A - f_n^2}{2f_n} &= \frac{1}{2 f_n}(A + f_n)
\end{align*}$$
从$f_0 = \sqrt{A_0}$开始迭代即可
这部分时间复杂度 $O(n \log n)$
这里要求 $A_0$ 是$\mod P$ 的二次剩余
可以用Cipolla算法求二次剩余
不过也可以用慢一些的算法，毕竟主要开销还是牛顿迭代.
选一个原根$g$，用bsgs算出阶 $ord$， 那么$g^{\frac{ord}{2}}$就是一个平方根.
这样的话，时间复杂度是$O(\sqrt P)$

## 多项式除法 `/` & 取余 `%`
除朴素除法外，其实有更快计算多项式带余除法的方法.
设$$A(x) = Q(x)B(x) + R(x)$$
其中 $\operatorname{deg}(A) = n$, $\operatorname{deg}(B) = m$
可得：$\operatorname{deg}(Q) = n - m$, $\operatorname{deg}(R) < m$
代入$\frac{1}{x}$
$$\begin{align*}
A(\frac{1}{x}) &= Q(\frac{1}{x})B(\frac{1}{x}) + R(\frac{1}{x}) \\
x^n A(\frac{1}{x}) &= x^{n - m}Q(\frac{1}{x}) x^m B(\frac{1}{x}) + x^n R(\frac{1}{x})\\
A^R(x) &= Q^R(x) B^R(x) + x^{n - \operatorname{deg}(R)} R^R(x)
\end{align*}$$
由于$n - \operatorname{deg}(R) > n - m$
所以等式两边的小于等于 $n - m$ 次项与 $R^R(x)$无关， 因为它乘上了$x^{n - \operatorname{deg}(R)}$这个系数
即
$$A^R(x) = Q^R(x) B^R(x) \mod x^{n - m + 1}\\
Q^R(x) = \frac{A^R(x)}{B^R(x)} \mod x^{n - m + 1}$$
于是通过一次多项式求逆和多项式乘法就可以算出$Q(x)$，而知道$Q(x)$后，$R(x)$就很容易计算了。

## 多项式多点求值 `eval(vector<int>x)`
其实就是使用分治去求解，不过可以通过一些科技去显著降低常数
### 朴素方法
求解$f(x_0),f(x_1) \dots f(x_{n - 1})$,设 $m = \lfloor\frac{n}{2}\rfloor$, $M_{l,r} = \prod_{i = l}^r (x-x_i)$
将$f(x)$ 拆成两部分:
$f(x) = M_{0,m}(x)P(x) + R(x)$
显然左边这部分对于$x = x_0, x_1,\dots,x_m$的贡献均为 $0$ 于是我们可以递归下去，对 $R$ 求解。
这里需要一次多项式取模，复杂度$O(n \log n)$，不过常数偏大。
而对于$x = x_{m + 1}, \dots , x_{n - 1}$， 我们模上 $M_{m + 1, n - 1}$ 同样递归求解即可。
构建 $M$ 我们使用分治ntt,时间复杂度是 $O(n \log^2 n)$
于是最后的时间复杂度 $T(n) = O(n \log n) + 2 T(\frac{n}{2}) \Rightarrow T(n) = O(n \log^2 n)$
实际上，很容易注意到一个点:
$$f(x_i) = f(x) \bmod (x - x_i)$$
我们上述做法不过是在分治地取模而已，类似于分治ntt(虽然这个是自顶向下的)

### Laurent 级数 / 转置原理(特勒根原理)
这里给出一个形式洛朗级数的式子
$$f(v) = [x^0]\frac{f(x^{-1})}{1 - vx}$$
这是好验证的，展开分母，$x^0$的系数显然是：
$$\sum_{i = 0}^{\infty} f_i v^i = f(v)$$
原理推导完毕，我们希望对于每一个 $v = x_i$ 计算出上式。
于是还是考虑分治：
设$M_{l, r} = \prod_{i = l} ^ r (1 - x_i x)$
我们从$\frac{f(x^{-1})}{M_{0, n - 1}}$开始递归， 从区间 $[l, r]$ 求解区间 $[l, m]$ 时,乘上$M_{m+1,r}$即可。
此时我们每次递归下去仅需要一次多项式乘法，相比多项式取模常数大大减小。

不过需要注意的是：这里的乘法不是一般的矩阵乘法！因为我们维护的是一个以$x^{-1}$为变量的多项式，所以这里实际上是差卷积，也可以从转置原理的角度理解为转置乘法。
因为我们希望最终得到$x^0$的系数，于是如果这个区间还有$k$个点值需要求解，我们将多项式截断到$x^{-k}$即可
递归过程的时间复杂度是类似的，为$O(n \log^2 n)$, 加上构建 $M$ 的时间复杂度 $O(n \log^2 n)$ 和一次多项式求逆 $O(n \log n)$， 总时间复杂度$O(n \log^2 n)$

当然，这个做法可以从朴素做法的转置这个角度来理解，不过可能需要对线性变换的理解到达一定程度。

## 多项式快速插值 `lagrange(vector<int>x, vector<int>y)`
设$M(x) = \prod_{i = 0}^n  (x - x_i)$
考虑lagrange插值公式：
$$\begin{align*}
f(x) &= \sum_{i = 0}^{n} y_i \prod_{j \neq i} \frac{x - x_j}{x_i - x_j}\\
\end{align*}$$
对于右边式子的分母，使用**洛必达法则**，有:
$$\prod_{j \neq i} \frac{1}{x_i - x_j} = \lim_{x\rightarrow x_i} \frac{x - x_i}{\prod_j x - x_j} 
= \lim_{x\rightarrow x_i} \frac{x - x_i}{M(x)} = \frac{1}{M'(x_i)}$$
于是
$$\begin{align*}
f(x) &= \sum_{i = 0}^{n} \frac{y_i}{M'(x_i)} \prod_{j \neq i} x - x_j\\
&= \sum_{i = 0}^{n} v_i \prod_{j \neq i} x - x_j
\end{align*}$$
分治ntt算出$M(x)$, 用多点求值求出$M'(x_i)$, 进一步求出 $v_i$
剩下的问题就是怎么计算上面那个和式
还是考虑分治，假设分治到区间$[l, r]$有结果
$$\begin{align*}
f_{l, r} &= \sum_{i = l}^r v_i\prod_{j \neq i, l \leq j \leq r}x - x_j \\
&= f_{l, m} \prod_{j = m + 1}^{r}x - x_j + f_{m + 1, r} \prod_{j = l}^{m}x - x_j
\end{align*}$$
前面分治ntt计算$M(x)$时预处理好连乘积多项式， 按照上式分治递归下去即可。
时间复杂度为$O(n \log^2 n)$

## 多项式平移

## 多项式连续点值平移

## 常系数齐次线性递推 
### Kitamasa/Fiduccia 算法 `kitamasa(vector<int>a, vector<int>c, i64 n)`

### 表示为有理函数 + Bostan–Mori 算法 `bostanMori(poly p, poly q, poly n)` `linearRecurrence(poly a, poly c, i64 n)`

## 最小多项式 Berlekamp Massey算法  `berlekampMassey`
$S(x) = P(x) + d x^n + ... \pmod {C(x)}$

## 多项式复合 `comp(poly g, int m)`
$h(x) = f(g(x)) \equiv [y^{0}] \frac{f(y^{-1})}{1 - yg(x)} \pmod {x^m}$

## 多项式复合逆 `revert(int m)`


# Todo:
1. 多项式复合
4. 多项式复合逆
5. 多项式平移
6. 常系数齐次线性递推 Bostan–Mori
7. Berlekamp Massey 最小多项式 (怎么两个都是BM)