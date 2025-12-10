实际上就是$len \geq 3$的置换生成的有标号$SET$

考虑枚举$len = n$， 再用EGF复合起来

$$
\begin{align*}
\hat{F_n}(x) &= \sum_{k = 0}^\infty \frac{1}{nk!} \frac{((n - 1)!)^k}{k!} \frac{nk!}{(n!)^k}x^{nk}\\
&= \sum_{k = 0}^\infty\frac{1}{k! n^k} x^{nk}\\
&= \sum_{k = 0}^\infty\frac{1}{k!} \left(\frac{x^n}{n}\right)^k\\
&= e^{\frac{x^n}{n}}
\end{align*}
$$

$$
\begin{align*}
\prod_{n = 3}^\infty \hat{F_n}(x) &= \prod_{n = 3}^\infty e^{\frac{x^n}{n}}\\
&= \exp(\sum_{n = 3}^\infty \frac{x^n}{n})
\end{align*}
$$

其实把求和补项变成$\ln$,可以得到闭式：
$$\frac{e^{-\frac{x^2}{2}-x}}{1 - x}$$