#include<bits/stdc++.h>
#define int long long
using i64 = long long;

using namespace std;

constexpr int P = 998244353;
constexpr int N = 2e5 + 10;
vector<int>fac, invfac;

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

void pre()
{
    fac.resize(N + 1);
    invfac.resize(N + 1);
    fac[0] = 1;
    for(int i = 1;i <= N;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[N] = power(fac[N], P - 2);
    for(int i = N - 1;i >= 0; i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }
    return;
}

int b(int n, int m)
{
    if(n < 0 || m < 0 || n < m)return 0;
    return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
}
int n,x;
int a[N];
int prea[N];
int ll[N];
int rr[N];
int pr[N];
int ke;
int cal(int xx)
{
    if(xx < 0) return 0;
    else if(xx > ke)
    {
        if( (xx % 2) == (ke % 2)) return pr[ke];
        else 
        {
            if(ke - 1 >= 0) return pr[ke - 1];
            else return 0;
        }
    }
    else return pr[xx];
}
int f(int l,int r)
{
    return (cal(r) - cal(l-2) + P)%P;
}
void solve()
{
    cin >> n >> x;
    map<int,int> ma;
    map<int,int> fin;
    for(int i = 1;i <= n;i++)
    {
        cin >> a[i];
        ma[a[i]]++;
    }
    int cnt = 0;
    for(const auto [a,b] : ma)
    {
        cnt++;
        prea[cnt] = b;
        fin[a] = cnt;
    }
    for(int i = 1;i <= cnt;i++)
    {
        prea[i] += prea[i-1];
    }
    for(int i = 1;i <= cnt;i++)
    {
        ll[i] = prea[i-1];
        rr[i] = prea[cnt] - prea[i];
    }
    int ans = 0;
    if(fin[x])
    {
        int id = fin[x];
        int m = ma[x];
        ke = ll[id] + rr[id];
        int l = ll[id];
        int r = rr[id];
        //cerr << ke << '\n';
        for(int i = 0;i <= ke;i++)
        {
            pr[i] = b(ke,i);
            //cerr << i << ' ' << pr[i] << '\n';
        }
        for(int i = 2;i <= ke;i++)
        {
            pr[i] = (pr[i] + pr[i-2])%P;
        }
        for(int i = 1;i <= m;i++)
        {
            int temp = b(m,i);
            temp = 1ll * temp * f(l + 2 - i - 1,l + 2 * i - i - 1) % P;
            ans = (ans + temp) % P;
            //cerr << i << ' '  << ans << '\n';
        }
        for(int i = 2;i <= m;i++)
        {
            int temp = b(m,i);
            //cerr << l + 2 - i - 2 << ' ' << l + 2 * (i-1) - i - 2 << '\n';
            temp = 1ll * temp * f(l + 2 - i ,l + 2 * (i-1) - i ) % P;
            ans = (ans + temp) % P;
            //cerr << i << ' ' << ans << '\n';
        }    
    }
    //cerr << ans << '\n';
    for(const auto [a,bb] : ma)
    {
        int c = 2 * x - a;
        if(c > a)
        {
            int l = ll[fin[a]];
            int r = rr[fin[c]];
            int ml = ma[a];
            int mr = ma[c];
            for(int i = 1;i <= ml;i++)
            {
                int temp = b(ml,i);
                temp = 1ll * temp * ((b(mr+l+r,l+i) - b(l+r,l+i) + P)%P)%P;
                ans = (ans + temp)%P;
            } 
        }
    }
    cout << ans << '\n';



}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    pre();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}

