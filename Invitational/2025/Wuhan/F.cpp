#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.31 16:07:41

constexpr int P = 998244353;

int power2(int p)
{
    int res = 1;
    int a = 2;
    while(p){
        if(p & 1)res = 1ll * res * a % P; 
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    ll n, m;
    cin>>n>>m;
    vector<ll>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin >> a[i] >> b[i];
    }

    vector<int>id(n);
    iota(id.begin(),id.end(),0);
    sort(id.begin(),id.end(),[&](int i, int j)->bool
    {
        return b[i] > b[j];
    });
    ll capsize = 0;
    ll remcnt = 0;
    ll ans = 0;
    constexpr ll INF = 1e15;
    for(int i = 0;i < n;i++){
        //sort as b[i]
        ll x = a[id[i]], y = b[id[i]];
        int ok = 0;
        //cerr<<x<<" "<<y<<endl;
        if(remcnt == 0){
            capsize = y;
            ll add = (x + m - 1) / m;
            ans += 1ll * add * power2(capsize) % P;
            ans %= P;
            remcnt = add * m - x;
        }
        else{
            while(capsize > y){
                remcnt *= 2;
                capsize--;
                if(remcnt > INF){
                    ok = 1;
                    break;
                }
            }
            if(remcnt >= x){
                remcnt -= x;
            }
            else{
                x -= remcnt;
                remcnt = 0;
                ll add = (x + m - 1) / m;
                ans += 1ll * add * power2(capsize) % P;
                ans %= P;
                remcnt = add * m - x;
            }
        }
        if(ok)break;
    }

    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}