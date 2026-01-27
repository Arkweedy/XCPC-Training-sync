```cpp
template<typename T>
T exgcd(T a, T b, T &x, T &y)
{
    x = 1, y = 0;
    array<T, 4>m = {1, 0, 0 ,1};//matrix
    while(b != 0){
        T c = a / b;
        m = {m[1], m[0] - c * m[1], m[3], m[2] - c * m[3]};
        T t = a % b;
        a = b;
        b = t;
    }
    x = m[0], y = m[2];
    return a;
}

i64 inv(i64 a, i64 m)
{
    i64 x, y;
    exgcd(a, m, x, y);
    if(x < 0)x += m;
    return x;
}

i64 crt(const vector<i64>&m, const vector<i64>&r)
{
    int n = m.size();
    i64 M = 1;
    for(int i = 0;i < n;i++){
        M *= m[i];
    }
    i128 ans = 0;
    for(int i = 0;i < n;i++){
        i128 c = inv(M / m[i], m[i]) * r[i] % M;
        ans = (ans + c * (M / m[i])) % M;
    }
    ans = (ans + M) % M;
    return ans;
}
```