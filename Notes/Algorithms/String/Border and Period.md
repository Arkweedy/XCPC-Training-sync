---
title : CF 2月部分题题解
date : 2025/2/2
mathjax : true
categories : [题解, Codeforces, ProblemSet]
cover : https://arkweedy.github.io/image/img020-hanamaru.png
---

# Border和周期
整理一下字符串中，Border,前缀函数和Z函数, 字符串的周期和阶,字符串的LCP(最长公共前缀)之间的关系和一些深刻的性质。

## 形式化规定
将集合 $\Sigma$ 称为字符集。字符集中的元素称为字符。字符的序列称为字符串。全体有限长度的字符串记为 $\Sigma^*$ ，长度为 $n$ 的字符串集合记为 $\Sigma^n$ 。字符串 $s,t$ 的连接写作 $st$ 。另设空串为 $\epsilon$ 。空串是连接运算的单位元。空串在字典序中定义为最小。由于连接运算满足结合律，在 $\Sigma^*$ 上构成幺半群。此幺半群称为自由幺半群。
记排除空串后的幺半群为 $\Sigma^+ = \Sigma^* - \epsilon$
将逆序字符串记为 $s^R = \mathrm{Reverse}(s)$
记 $s$ 的前缀集/后缀集 为 $\mathrm{Pref}(s), \mathrm{Suf}(s)$,真前缀集/真后缀集为$\mathrm{Pref^*}(s), \mathrm{Suf^*}(s)$
记字符串 $s$ 的第 $i$ 个字符为 $s[i]$, 从第 $l$ 到第 $r$ 个字符组成的字串为$s[l : r]$

## Border与周期 
### 定义与基本性质
定义字符串 $s$ 的border为一对匹配的真前缀-后缀(即公共真前后缀), 最长的border记为 $\operatorname{border}(s)$。
定义字符串 $s$ 的周期Period为使得 $\forall i \leq |s|,s[i \bmod p] = s[i]$ 成立的整数 $p$, 将满足条件的最小正整数记为最小周期，记作 $\operatorname{period}(s)$。
定义字符串的阶order：若字符串$s$的最小周期 $d$ 整除 $|s|$, 则字符串 $s$的阶 $\operatorname{ord}(s) = \frac{|s|}{d}$ ,否则 $\operatorname{ord}(s) = 1$。
定义字符串的border集和周期集：
$$B(s) = \{i \mid s[1:i]\text{是s的border}\} \\
P(s) = \{i \mid \text{i是s的周期} \}$$
border有一些非常好的性质:
1. 字符串的所有border是可以递归计算的，即字符串的border要么是最大border，要么就是最大border的border。这是很容易理解的。
所以我们通过遍历$\operatorname{border}(s),\operatorname{border^2}(s),...,\operatorname{border^k}(s) = \epsilon$即可找到一个字符串的所有border.
1. 字符串的每个border都对应字符串的一个周期。若border为 $s[1:i]$,那么对应的周期长为 $|s| - i$.这是易证的: 我们写出border的对应关系: $s[k] = s[n - i + k]$ ,那么 $s$显然满足 $s[k] = s[k \bmod n - i ]$。形式化来说， $\forall b \in B(s), |s| - b \in P(s)$。

### [Fine–Wilf 定理(强周期定理)](https://en.wikipedia.org/wiki/Fine_and_Wilf%27s_theorem)
先引入一些周期的性质：
1. 如果字符串的最小周期可以整除字符串的长度，那么字符串的所有周期都是字符串最小周期的整数倍，反之则不一定。
2. 弱周期定理：




## 前缀函数$\pi$ 和 KMP算法
前缀函数 $\pi$ 定义为: $\pi(i) = |\operatorname{border}(s[1:i])|$ ,即 $\pi(i)$ 表示字符串 $s$ 长 $i$ 的前缀的Border的长度。




