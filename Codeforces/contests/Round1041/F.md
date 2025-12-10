function f(array a):    
pos := 1    
res := 0    
let nxt[x] be an array such that
nxt[x] is the smallest index y such that
y > x and a[y] > a[x], or undefined if no such y exists    
while pos < n:        
if a[pos] < a[n]:            
    res += a[nxt[pos]] - a[pos]            
    pos := nxt[pos]        
else:            
    pos += 1    
return res

枚举局部最大值ma，位于下标i，前缀和为sum,个数为cnt个
如果m - sum >= ma,有贡献式
$$cnt\times\sum_{k = 1}^{n - i} \frac{\binom{m - sum}{k - 1}}{k}$$
前缀最大值的dp转移？
维护x,i,sum,cnt?肯定不行
直接枚举位置，最大值？似乎可行，但是得在前缀上再加计数限制。
怎么去拆解前缀？
似乎是生成函数？小于等于k序列的生成函数是
$$a_k = \sum_{n = 1}^k x^n = \frac{x^{k + 1} - 1}{x - 1}$$
于是，
$$cnt = [x^{sum - ma}] (a_{ma})^{i - 1} = ...$$

于是答案变成求和：
$$\sum_{ma = 1}^{m} \sum_{sum = ma}^{m} \sum_{i = 1}^{n}  [x^{sum - ma}] (a_{ma})^{i - 1} *  \frac{\binom{m - sum}{n - i - 1}}{n - i}$$

但是我不会算qwq






