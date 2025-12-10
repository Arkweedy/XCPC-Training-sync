#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 1e6;
vector<int>cnt;
bitset<N + 1>isprime;
vector<int>prime;

void seive()
{
    cnt.resize(N + 1);
    isprime.set();
    for(int i = 2;i <= N;i++){
        if(isprime[i]){
            cnt[i] = 1;
            prime.push_back(i);
        }
        for(const auto &p : prime){
            if(i * p > N)break;
            cnt[i * p] = cnt[i] + 1;
            isprime[i * p].flip();
            if(i % p == 0)break;
        }
    }
}

int L(const int &x,const int &d)
{
    return x - x / d * d;
};
int R(const int &x,const int& d)
{
    return (x + d - 1) / d * d - x;
};
int l(const int &x,const int &d)
{
    return x / d;
};
int r(const int &x,const int &d)
{
    return (x + d - 1) / d;
};

void solve()
{
    int n,m;
    cin>>n>>m;
    if(n > m)swap(n,m);
    int d = abs(n - m);
    map<int,int>mp;
    auto get_cnt = [&](int x)->int
    {
        if(x <= N)return cnt[x];
        else{
            if(mp.count(x))return mp[x];
            int res = 0;
            int y = x;
            for(const auto&p : prime){
                while(x % p == 0){
                    x /= p;
                    res++;
                }
                if(x <= N){
                    res += cnt[x];
                    x = 0;
                    break;
                }
            }
            res += (x != 0 ? 1 : 0);
            mp[y] = res;
            return res;
        }
    };

    
    vector<int>fac;
    for(int i = 1;i * i <= d;i++){
        if(d % i == 0){
            fac.push_back(i);
            if(i * i != d)fac.push_back(d / i);
        }
    }
    
    sort(fac.begin(),fac.end());
    int len = fac.size();
    constexpr int inf = 1145141919;
    vector<int>dp0(len, inf),dp1(len, inf);
    vector<int>fcnt(len);//
    
    dp0[0] = dp1[0] = 0;
    for(int i = 0;i < len;i++){
        for(int j = i + 1;j < len;j++){
            if(fac[j] % fac[i] == 0){//i->j
                int a = l(n,fac[i]), b = r(n, fac[i]);// a(+1) -> b(+1)
                int c = l(n,fac[j]), d = r(n, fac[j]);
                int f = fac[j] / fac[i];// divide by f
                int x = get_cnt(f);// use c
                dp0[j] = min(dp0[j], x + dp0[i] + L(a,f));
                dp1[j] = min(dp1[j], x + dp1[i] + R(b,f));
                if(l(b,f) == c)dp0[j] = min(dp0[j], x + dp1[i] + L(b,f));
                else dp1[j] = min(dp1[j], x + dp1[i] + L(b,f));
                if(r(a,f) == c)dp0[j] = min(dp0[j],x + dp0[i] + R(a,f));
                else dp1[j] = min(dp1[j],x + dp0[i] + R(a,f));
            }
        }
    }    
    
    int ans = inf;
    for(int i = 0;i < len;i++){
        ans = min(ans, min(dp0[i] + l(n,fac[i]) - 1, dp1[i] + r(n,fac[i]) - 1));
    }
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    seive();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}