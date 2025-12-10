$$\hat{F}(x) = x e^{\hat{G}(x)}$$
其中
$$[x^n] (2^n-1)\hat{F}(x) = [x^n]\hat{G}(x)$$

推理：
设$n$元无向连通图的EGF为$\hat{C}(x)$
考虑n号点至少要和每个连通图连一条边，去掉一个点后原图变成若干个连通块
考虑定下根的n元有标号连通图与一个点相连生成的EGF为$\hat{F}(x)$
有:$f_n = n c_n$
$$
\begin{align*}
\hat{C_n}(x) &= \sum_{k = 0}^\infty \frac{1}{nk!} \frac{((2^n - 1)c_n)^k}{k!} \frac{nk!}{(n!)^k}x^{nk}\\
&= \exp(\frac{(2^n - 1)c_n}{n!})\\
\hat{F}(x) &= x\prod_{n = 1}^{\infty}\hat{C_n}(x)\\
&= x \exp(\sum_{n = 1}^\infty (2^n - 1)\hat{c_n})\\
&= x e^{\hat{G}(x)}\\
\end{align*}
$$

$$\begin{align*}
    \hat{F}(x) &=  x e^{\hat{G}(x)}\\
    \ln \hat{F}(x) &=  \ln x + \hat{G}(x)\\
    \frac{\hat{F'}(x)}{\hat{F}(x)} &= \frac{1}{x} + \hat{G'}(x)\\
    x\hat{F'}(x) &= \hat{F}(x) + \hat{F}(x) x \hat{G'}(x)\\
    n\hat{f_n} &= \hat{f_n} + \sum_{k = 1}^{n - 1} \hat{f}_{n - k} k \hat{g}_k\\
    \hat{g}_n &= (2^n - 1)\hat{c}_n\\
    &= \frac{2^n - 1}{n}\hat{f}_n \\
    \hat{f}_n &= \frac{1}{n - 1} \sum_{k = 1}^{n - 1}\hat{f}_{n - k} (2^k - 1)\hat{f_k}
\end{align*}$$

令$h_n = (2^n - 1) \hat{f}_n$,跑在线卷积即可。


其实更好的办法是令$\hat{A}(x)$为无向图的EGF
有：$$\hat{A}(x) = \exp(\hat{C}(x))$$
而 $$\hat{A}(x) = \sum_{n} 2^{\binom{n}{2}} \frac{x^n}{n!}$$
来个多项式 $\ln$即可


