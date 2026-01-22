#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.22 10:28:33
constexpr int P = 998244353;
constexpr int G = 3;
int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int power(int a, int p, int M)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % M;
        a = 1ll * a * a % M;
        p >>= 1;
    }
    return res;
}




int inv(int a)
{
    return power(a, P - 2);
}

constexpr int MAX_LEN = 20;

const array<int, 1 << MAX_LEN>omega()
{
    array<int, 1 << MAX_LEN>res;
    res.fill(1);
    for(int i = 1;i <= (1 << MAX_LEN - 1); i <<= 1){
        int wi = power(G, (P - 1) / (i * 2));
        for(int j = 1;j < i;j++){
            res[i + j] = 1ll * res[i + j - 1] * wi % P;
        }
    }
    return res;
}

const array<int , 1 << MAX_LEN>W = omega();

void dft(vector<int>&f){
    int n = f.size();
    for(int k = n >> 1;k;k >>= 1){
        for(int i = 0;i < n;i += k << 1){
            for(int j = 0;j < k;j++){
                int x = f[i + j];
                int y = f[i + j + k];
                int s = x + y;
                if(s >= P)s -= P;
                f[i + j] = s;
                int d = x - y;
                if(d < 0)d += P;
                f[i + j + k] = 1ll * d * W[k + j] % P;
            }
        }
    }
    return;
}

void idft(vector<int>& f)
{
    int n = f.size();
    int invn = inv(n);
    for(int k = 1;k < n;k <<= 1){
        for(int i = 0;i < n;i += k << 1){
            for(int j = 0;j < k;j++){
                int x = f[i + j];
                int y = 1ll * f[i + j + k] * W[k + j] % P;
                int s = x + y;
                if(s >= P)s -= P;
                int d = x - y;
                if(d < 0)d += P;
                f[i + j] = s;
                f[i + j + k] = d;
            }
        }
    }

    for(int i = 0;i < n;i++){
        f[i] = 1ll * f[i] * invn % P;
    }
    reverse(f.begin() + 1, f.end());
    return;
}

vector<int> operator* (vector<int>a, vector<int>b)
{
    if(a.size() == 0 || b.size() == 0){
        return vector<int>(0);
    }
    if(a.size() < b.size()){
        swap(a, b);
    }
    int n = 1, tot = a.size() + b.size() - 1;
    while(n < tot)n *= 2;
    if(b.size() < 128){
        vector<int>c(tot);
        for(int i = 0;i < a.size();i++){
            for(int j = 0;j < b.size();j++){
                c[i + j] = (c[i + j] + 1ll * a[i] * b[j]) % P;
            }
        }
        return c;
    }
    a.resize(n);
    b.resize(n);
    dft(a);
    dft(b);
    for(int i = 0;i < n;i++){
        a[i] = 1ll * a[i] * b[i] % P;
    }
    idft(a);
    a.resize(tot);
    return a;
}



void solve()
{
    int n;
    string s;
    cin >> n >> s;
    reverse(s.begin(), s.end());
    if(n == 1){
        cout << s << endl;
        return;
    }
    auto build = [&](auto&&self, int l, int r)->vector<int>
    {
        if(l == r){
            int p = power(2, l - 1, P - 1);
            int x = power(10, p);
            return vector<int>{1, x};
        }
        int m = l + r >> 1;
        return self(self, l, m) * self(self, m + 1, r);
    };

    auto f = build(build, 1, n - 1);
    i64 ans = 0;
    for(int i = 0;i < n;i++){
        ans = (ans + 1ll * (s[i] - '0') * f[i]) % P;
    }
    cout << ans << endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}