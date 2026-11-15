$n \rightarrow N = 2^{n} - 1$ 
1 - n
多少个点 $2^{k - 1}$ 
first $2^{k - 1}$
$sz(k) = 2^{n - k + 1} - 1$
$con(k) = (sz(k + 1) + 1)^2 + (N - sz(k))$
$layer(k) = \dots$
$ans = \sum_i layer(i)$