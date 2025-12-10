定义$s_i = \sum_j {a_j}^i$
定义平衡多项式$$E(x) = \prod_i (1 + a_i x)$$
有：
$$e_1 = s_1$$
$$e_2 = \frac{s_1^2 - s_2}{2}$$
$$e_3 = \frac{s_1^3 - 3s_1s_2 + 2s_3}{6}$$

推理:
$$\begin{align*}
    E(x) &= \prod_i (1 + a_i x) \\
    \ln E(x) &= \sum_i \ln(1 + a_i x) \\
    &= \sum_i \sum_{j = 1} \frac{(-1)^{j - 1}}{j} (a_ix)^j \\
    &= \sum_{j = 1} \frac{(-1)^j}{j} (s_ix)^j \\
    \frac{E'(x)}{E(x)} &= \sum_{j = 1} (-1)^{j - 1}s_i^j x^{j - 1} \\
    xE'(x) &= E(x) \sum_{j = 1} (-1)^{j - 1}s_i^j x^{j}\\
    ke_k &= \sum_{i = 1}^{k} (-1)^{k - 1} e^{k - i}s^k
\end{align*}$$
