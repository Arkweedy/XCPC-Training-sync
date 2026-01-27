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

int inv(i64 a, i64 m)
{
    i64 x, y;
    exgcd(a, m, x, y);
    x = (x % m + m) % m;
    return x;
}

int power(int a, int p, int P)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int bsgs(int a, int b, int p)
{
    a %= p;
    b %= p;
    if(p == 1) return 0;
    if(b == 1) return 0;
    
    int sq = ceil(sqrt(p));

    unordered_map<int,int>mp;
    mp.reserve(sq * 2);
    int x = 1;
    for(int i = 0;i <= sq;i++){
        mp[1ll * x * b % p] = i;
        x = 1ll * x * a % p;
    }

    int asq = power(a, sq, p);
    int y = asq;
    for(int i = 1;i <= sq;i++){
        if(mp.find(y) != mp.end()){
            return i * sq - mp[y];
        }
        y = 1ll * y * asq % p;
    }
    return -1;
}

int exbsgs(int a, int b, int p)
{
    a %= p;
    b %= p;
    if(p == 1 || b == 1)return 0;
    if(a == 0){
        if(b == 0)return 1;//0^0 = ? 
        else return -1;
    }

    int k = 0;
    int d = 1;
    while(1){
        int g = gcd(a, p);
        if(g == 1)break;
        if(b % g != 0)return -1;
        p /= g;
        b /= g;
        d = 1ll * d * (a / g) % p;
        k++;
        if(d == b)return k;
    }
    
    int r = 1ll * b * inv(d, p) % p;
    int res = bsgs(a, r, p);
    if(res == -1)return -1;
    else return res + k;
}
```