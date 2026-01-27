excrt
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

i64 excrt(const vector<i64>& m, const vector<i64>& r)
{
    int n = m.size();
    i128 R = r[0];
    i64 M = m[0];
    for(int i = 1;i < n;i++){
        i64 x, y;
        i64 g = exgcd(M, m[i], x, y);
        assert((r[i] - R) % g == 0);
        i128 z = x * ((r[i] - R) / g);
        R = z * M + R;
        M = lcm(M , m[i]);
        R = (R % M + M) % M;
    }
    return (i64)R;
}
```
