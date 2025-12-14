尝试推导一下C
一步一步来：
形式化题意大概是：
有随机均匀分布$U_x \sim \mathrm{Uniform(0,x)}$
问 $U_x$ 之和超过$1$的期望个数。

有使用一些标准概率分布公式的方法，不过我们尝试另外一种基于离散化和极限+生成函数的推导路径，标准概率公式变换的方法在后面给出。

## 推导1
设取$n$次的值小于$1$的概率为$P(n)$.
定义$P(0) = 1$
那么答案即为$$\sum_{n = 0}^{\infty}P(n)$$
我们不妨将$[0,x]$切分成$Nx$份，每次可以取$0, 1,2,\dots,Nx$份，每份大小为$\frac{1}{N}$。
因为要小于我们不妨设取$n + 1$次取到了$N$份，分别为$v_1,v_2,\dots, v_{n+ 1}$,其中$v_i \in \{0, 1, 2,\dots, Nx\}$，特殊地，$v_{n + 1} \geq 0$即可，不受$v_i \leq Nx$的约束
我们使用生成函数分析得到取$n + 1$次的情况,使用OGF:
~~这里的形式元和变量$x$似乎混用了()~~
$$\begin{align*}
F(x) &= \left(1 + x + x^2 + \dots + x^{Nx} \right) ^ {n} \frac{1}{1 - x} \\
&= \left(\frac{1 - x^{Nx + 1}}{1 - x} \right) ^ {n} \frac{1}{1 - x}\\
&= (1 - x^{Nx + 1})^{n}(1 - x)^{-(n + 1)} \\
&= \left(\sum_{i = 0}^{n}  \binom{n}{i} (-1)^{i} (x^{Nx + 1})^{i} \right) \left(\sum_{k = 0}^{\infty} \binom{- n - 1}{k} (-1)^{k}x^k  \right)
\end{align*}$$

而刚好取到$N$份的情况数是$[x^N]F(x)$
于是情况数为：
$$\begin{align*}
[x^N]F(x)&= \sum_{i = 0}^{n} \binom{n}{i} \binom{-n - 1}{N - (Nx + 1)i} (-1)^{N(xi - 1)} 
\end{align*}$$
不太会化简()
然而存在这么一个恒等式：
$$[x^m](1-x)^{-(n + 1)} = \binom{n + m}{m}$$
这是好证的，使用广义二项式定理，
$$(1-x)^{-(n + 1)} = \sum_{i = 0}^{\infty}\binom{-n - 1}{i}(-x)^i = \sum_{i = 0}^{\infty}\frac{(n + 1)^{\overline{i}}}{i !}x^i =\sum_{i = 0}^{\infty} \binom{n + i}{i}x^i$$

于是我们继续愉快化简：
$$\begin{align*}
[x^N]F(x)&= \sum_{i = 0}^{n} \binom{n}{i} \binom{n + N(1 - xi) - i}{N(1 - xi) - i} (-1)^{i} \\
&= \sum_{i = 0}^{n} \binom{n}{i} \frac{(n + N(1 - xi) - i)^{\underline{n}}}{(n !)} (-1)^{i}
\end{align*}$$

于是概率
$$\begin{align*}
P(n) &= \frac{[x^N]F(x)}{(Nx + 1)^{n}} \\
&= \frac{1}{(Nx + 1)^{n}}\sum_{i = 0}^{n} (-1)^{i}\binom{n + 1}{i} \frac{(n + N(1 - xi) - i)^{\underline{n}}}{(n !)}\\ 
\lim_{N \rightarrow \infty}P(n)&=\frac{1}{(Nx + 1)^{n}}\sum_{i = 0}^{n} (-1)^{i}\binom{n + 1}{i} \frac{(N)^n(1 - xi)^{n}}{(n !)}\\
&=\frac{1}{n!}\sum_{i = 0}^{n} (-1)^{i}\binom{n}{i} \left(\frac{1 - xi}{x}\right)^{n}\\
&=\frac{1}{n!}\sum_{i = 0}^{\frac{1}{x}} (-1)^{i}\binom{n}{i} \left(\frac{1 - xi}{x}\right)^{n}\\
\end{align*}$$

<!-- 于是$P(n)$ 的OGF为
$$\frac{1}{n!}\sum_{i = 0}^{n} (-1)^{n - i}\binom{n}{i} \left(\frac{xi - 1}{x}\right)^{n}$$ -->

于是期望轮数为
不妨设$a_i = \frac{1 - xi}{x}$
$$\begin{align*}
\sum_{n = 0}^{\infty}P(n)
&=\sum_{n = 0}^{\infty}\sum_{i = 0}^{\frac{1}{x}} (-1)^{i}\binom{n}{i} \frac{a_i^{n}}{n!}\\
&=\sum_{i = 0}^{\frac{1}{x}}(-1)^{i}\sum_{n = i}^{\infty}\binom{n}{i} \frac{a_i^{n}}{n!}\\
&=\sum_{i = 0}^{\frac{1}{x}}(-1)^{i} \frac{a_i^i}{i !} e^{a_i}
\end{align*}$$

直接算这个就行。

顺便补一下最后一步的变换：
$$\begin{align*}
    &\sum_{n = 0}^{\infty} \binom{n}{k} \frac{a^n}{n!}\\
    =&\sum_{k = 0}^{\infty} \frac{a^n}{k!(n - k)!}\\
    =&\frac{a^k}{k}\sum_{k = 0}^{\infty} \frac{a^{n-k}}{(n - k)!}\\
    =& \frac{a^k}{k}e^a
\end{align*}$$

## 推导2

利用**Irwin–Hall 分布**（也叫 uniform sum 分布）


CDF 与 PDF（标准型 $[0,1]$）
对任意 $x \in [0,n]$ ，其累积分布函数（CDF）与密度（PDF）为
$$F_n(x) = \Pr(X_n \leq x) = \frac{1}{n!} \sum_{k=0}^{\lfloor x \rfloor} (-1)^k \binom{n}{k} (x-k)^n$$
$$f_n(x) = F'_n(x) = \frac{1}{(n-1)!} \sum_{k=0}^{\lfloor x \rfloor} (-1)^k \binom{n}{k} (x-k)^{n-1}$$

于是我们把原问题转化为标准$[0,1]$分布下，不大于$\frac{1}{x}$的概率。
代入$F_n(x)$,
$$P(n) = F_n(\frac{1}{x}) =  \frac{1}{n!} \sum_{k=0}^{\lfloor x \rfloor} (-1)^k \binom{n}{k} \left(\frac{1 - kx}{x}\right)^n$$

对$P(n)$无穷求和上同。
