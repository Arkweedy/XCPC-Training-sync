#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//P1919.cpp Create time : 2026.01.13 22:37

using c64 = complex<double>;
constexpr c64 I = c64(0, 1);
constexpr double PI = numbers::pi; //c++20

void dft(vector<c64>&f, int inv)
{
    int n = f.size();
    int j = 0;
    for(int i = 1;i < n;i++){
        int k = n >> 1;
        for(;k & j;k >>= 1){
            j ^= k;
        }
        j ^= k;
        if(j < i){
            swap(f[i], f[j]);
        }
    }

    for(int len = 2;len <= n;len <<= 1){
        double ang = 2 * PI / len * inv;
        c64 wlen = c64(cos(ang), sin(ang));
        vector<c64>w(len / 2);
        w[0] = 1;
        for(int i = 1;i < len / 2;i++){
            w[i] = w[i - 1] * wlen;
        }
        for(int i = 0;i < n;i += len){
            for(int j = 0;j < len / 2;j++){
                c64 u = f[i + j], v = f[i + j + len / 2] * w[j];
                f[i + j] = u + v;
                f[i + j + len / 2] = u - v;
            }
        }
    }

    if(inv == 1){
        for(int i = 0;i < n;i++){
            f[i] /= n;
        }
    }
    return;
}

void fft(vector<c64>& f)
{
    int n = 1;
    while(n < f.size())n *= 2;
    f.resize(n);
    dft(f, -1);
    return;
}

void ifft(vector<c64>& f)
{
    int n = 1;
    while(n < f.size())n *= 2;
    f.resize(n);
    dft(f, 1);
    return;
}

vector<i64> operator*(vector<i64>& a, vector<i64>& b)
{
    int m = a.size() + b.size() - 1;
    int n = 1;
    while(n < m)n *= 2;
    vector<c64>f(n), g(n);
    for(int i = 0;i < a.size();i++){
        f[i] = a[i];
    }
    for(int i = 0;i < b.size();i++){
        g[i] = b[i];
    }
    fft(f);
    fft(g);
    for(int i = 0;i < n;i++){
        f[i] *= g[i];
    }
    ifft(f);
    vector<i64>res(m);
    for(int i = 0;i < m;i++){
        res[i] = llround(f[i].real());
    }
    return res;
}

void solve()
{
    string a, b;
    cin >> a >> b;
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    vector<i64>f(a.length()), g(b.length());
    for(int i = 0;i < a.length();i++){
        f[i] = a[i] - '0';
    }
    for(int i = 0;i < b.length();i++){
        g[i] = b[i] - '0';
    }
    auto h = f * g;
    h.resize(h.size() + 1);
    for(int i = 0;i < h.size() - 1;i++){
        h[i + 1] += h[i] / 10;
        h[i] %= 10;
    }
    while(!h.back())h.pop_back();
    reverse(h.begin(),h.end());
    for(auto x : h){
        cout << x;
    }
    cout << endl;
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