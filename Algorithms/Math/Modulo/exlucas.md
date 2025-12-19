首先考虑模素数幂下的求解，剩下的只需要套一层crt就行
计算$$\binom{n}{m} = \frac{n!}{m!(n - m)!} = p^{\nu_p(n!) - \nu_p(m!) - \nu_p((n - m)!)} \frac{(n!)_p}{(m!)_p ((n - m)!)_p} \mod p^k$$
考虑$\mod p$ 下，把 $p$ 幂次单独拆出来：
$$n! =  p^{\nu_p(n!)} (n!)_p$$
根据Legendre公式，有：
$$\nu_p(n!) = \sum_{i = 1}^\infty \left\lfloor\frac{n}{p^i}\right\rfloor = \frac{n - S_p(n)}{p - 1}$$
其中，$S_p(n)$ 为 $p$ 进制下 $n$ 的各个数位的和。
这个公式的由来与 $n$ 在 $p$ 进制 下的表示有关
参考实现：
```c++
// Obtain multiplicity of p in n!.
int multiplicity_factorial(int n, int p) {
  int count = 0;
  do {
    n /= p;
    count += n;
  } while (n);
  return count;
}
```

而对于另外一部分，有模素数和模素数幂的公式：
$$(n!)_p \equiv (-1)^{\lfloor\frac{n}{p}\rfloor} (n \bmod p)! (\lfloor\frac{n}{p}\rfloor !)_p \pmod p$$
$$(n!)_p \equiv (\pm 1)^{\lfloor\frac{n}{p ^\alpha}\rfloor} \left(\prod_{1 \leq j \leq (n \bmod p^\alpha), j \perp p} j \right) (\lfloor\frac{n}{p}\rfloor !)_p \pmod {p^\alpha}$$
**注意第二个公式哪些地方整除$p$, 那些地方整除$p^\alpha$**
对于第二个公式中的$\pm 1$，其取值与Wilson定理的推广的取值条件一致：

$$\prod_{1 \leq k \leq p^\alpha, k \perp p} k \equiv 
\begin{cases}
1, & p = 2 \&\& \alpha \geq 3\\
-1, & \text{otherwise}\\
\end{cases}$$

利用这个式子，我们就可以递归计算 $(n!) \mod p^\alpha$






