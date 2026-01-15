#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//fft.cpp Create time : 2026.01.13 05:43

using c64 = complex<double>;
constexpr c64 I = c64(0, 1);
const double PI = acos(-1.0);


void dft(vector<c64>&f, int inv)
{
    int n = f.size();
    if(n == 1)return;
    vector<c64>l(n / 2), r(n / 2);
    for(int i = 0;i < n / 2;i++){
        l[i] = f[i * 2];
        r[i] = f[i * 2 + 1];
    }
    dft(l, inv);
    dft(r, inv);

    double ang = 2 * PI / n * inv;
    c64 w(1), wn(cos(ang),sin(ang));

    for(int i = 0;i < n / 2;i++){
        c64 u = l[i], v = w * r[i];
        f[i] = u + v;
        f[i + n / 2] = u - v;
        w *= wn;
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
    for(int i = 0;i < n;i++){
        f[i] /= n;
    }
    return;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<c64>a(n + m + 1), b(n + m + 1);
    for(int i = 0;i <= n;i++){
        int x;
        cin >> x;
        a[i] = x;
    }
    for(int i = 0;i <= m;i++){
        int x;
        cin >> x;
        b[i] = x;
    }
    fft(a);
    fft(b);
    for(int i = 0;i < a.size();i++){
        a[i] *= b[i];
    }
    ifft(a);
    for(int i = 0;i <= n + m;i++){
        cout << (i64)llround(a[i].real()) << " ";
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