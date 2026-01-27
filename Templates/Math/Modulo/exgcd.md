```c++
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