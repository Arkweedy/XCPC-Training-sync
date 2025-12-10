用$f_{k,i}$表示第$k$轮，颜色为$i$的个数,$i$为0base

$$f_{k,i} = \sum_{j = 1}^{n - 1}f_{k - 1,i + j \bmod n} a_i\\
\frac{f_{k,i}}{a_i} = \sum_{j = 1}^{n - 1}f_{k - 1,i + j \bmod n}$$
令
$$F = \sum_{n} \frac{f_n}{a_n}x^n$$
$$G = \sum_{n} f_n x^n$$
$$H = \sum_{i = 1}^n x^i$$

那么有
$$F_k = G_{k - 1}H \mod x^n - 1$$

目标是计算：$f_{T,0}$

