exgcd
```cpp
int ex_gcd(int a, int b, int& x, int& y) {
    if (!b) {
      x = 1;
      y = 0;
      return a;
    } else {
        int g = ex_gcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}

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
    x = (x % m + m) % m;
    return x;
}
```

exlucas
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
    x = (x % m + m) % m;
    return x;
}

class Calcer{
    int p, a, pa;
    vector<int>f;
    
    i64 nu(i64 n)
    {
        i64 cnt = 0;
        do{
            n /= p;
            cnt += n;
        }while(n);
        return cnt;
    }

    i64 fac(i64 n)
    {
        int neg = p != 2 || pa <= 4;
        i64 res = 1;
        while(n > 1){
            if((n / pa) & neg)res = pa - res;
            res = res * f[n % pa] % pa;
            n /= p;
        }
        return res;
    }

    public:
    Calcer(int p, int a, int pa)
        :p(p),a(a),pa(pa),f(pa)
    {
        f[0] = 1;
        for(int i = 1;i < pa;i++){
            f[i] = i % p ? 1ll * f[i - 1] * i % pa : f[i - 1];
        }    
    }

    int binom(i64 n, i64 k)
    {
        i64 v = nu(n) - nu(k) - nu(n - k);
        if(v >= a)return 0;
        i64 res = fac(n - k) * fac(k) % pa;
        res = fac(n) * inv(res, pa) % pa;
        while(v--)res *= p;
        return res % pa;
    }
};

class MComb{
    int m;
    //vector<int>_fac, _invfac;
    vector<Calcer>calcer;
    vector<int>crt_coef;    

public:
    MComb(int n)
        :m(n)
    {
        for(int i = 2;i * i <= n;i++){
            if(n % i == 0){
                int x = 0, y = 1;
                while(n % i == 0){
                    x++;
                    y *= i;
                    n /= i;
                }
                calcer.emplace_back(i, x, y);
                crt_coef.push_back(1ll * m / y * inv(m / y, y) % m);
            }
        }
        if(n > 1){
            calcer.emplace_back(n, 1, n);
            crt_coef.push_back(1ll * m / n * inv(m / n, n) % m);
        }
    }

    int binom(i64 n, i64 k)
    {
        i64 res = 0;
        for(int i = 0;i < calcer.size();i++){
            res = (res + 1ll * calcer[i].binom(n, k) * crt_coef[i]) % m;
        }
        return res;
    }
};

```

crt
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