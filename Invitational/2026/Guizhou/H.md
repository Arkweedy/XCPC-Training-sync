按照题意，要求所有置换环长度均小于等于 $k$ 的长为 $n$ 的排列的个数
其实有很多方法，OGF/EGF都可以，也可以从组合意义出发

考虑使用EGF:
是置换环生成了这个集合，那么我们描述一下置换环的EGF
环长为 $n$ 的置换环有 $(n - 1)!$ 种，那么有
$$\hat{C}_k(x) = \sum_{n = 1}^{k} \frac{(n - 1)!}{n!}x^n = \sum_{n = 1}^{k} \frac{x^n}{n}$$
于是合法排列的EGF与环计数的EGF有这样的关系：
$$\hat{A}(x) = e^{\hat{C}_k(x)} = \exp(\sum_{n = 1}^{k} \frac{x^n}{n})$$

也可以从 cycle count profile 的角度构造一个关于归一化答案 $\frac{A_n}{n!}$ 的 OGF。它不是直接关于 $A_n$的 OGF，而是关于 $f_n = \frac{A_n}{n!}$的普通生成函数。
也可以考虑使用OGF
我们从小到大枚举环的种类数，并附上对应的系数进行去重，最后乘上 $n!$ 把排列映射到环结构上
考虑环长为 $m$ 的环,多个环他们之间彼此不区分，环的轨道大小是 $m$ ，因此OGF是
$$C_m(x) = \sum_{c = 0}^{\infty} \frac{x^{cm}}{c! m^c} = \sum_{c = 0}^{\infty} \frac{(\frac{x^m}{m})^c}{c!} = e^{\frac{x^m}{m}}$$
于是答案就是按照顺序把这些OGF乘起来，最后再乘上$n!$
可以发现OGF和EGF的推导结果是一样的。

实际上更严谨的写法是
$$G(x) = \sum_{N \geq 0} \left( \sum_{\substack{c_1, \ldots, c_k \geq 0 \\ \sum_{m=1}^k m c_m = N}} \prod_{m=1}^k \frac{1}{m^{c_m} c_m!} \right) x^N$$
这个式子在经过交换求和等等操作后，恰好等于上面的$C_m(x)$的乘积

设$$F(x) = \exp\left(\sum_{n = 1}^{k} \frac{x^n}{n}\right)$$
问题在于怎么求解$[x^n] F(x)$
直接构造多项式再exp时间复杂度/模数都不行。

不过我们可以求导发现：
$$\begin{align*}
F'(x) = (\sum_{i = 0}^{k - 1}x^i)F(x) = \frac{1-x^k}{1-x} F(x)\\
(1-x)F'(x) = (1-x^k)F(x)
\end{align*}$$
两边取$x^{n - 1}$次系数，有
$$\begin{align*}
nf_n - (n - 1)f_{n - 1} = f_{n - 1} - f_{n - k - 1}\\
f_n = f_{n - 1} - \frac{f_{n - k - 1}}{n}
\end{align*}$$
根据定义，对于 $0 \leq n \leq k$, $f_n = 1$， 因为这代表全部排列都是合法的(乘上$n!$即全部),对于$n < 0 , f_n = 0$
对于$n > k$, 使用这个递推式即可。
另外一个疑问：EGF得到的系数是一个类似于比例/概率的东西吗？应该怎么理解它具体的数值，以及OGF路径的计算方法怎么从逻辑/形式上严谨描述呢？
