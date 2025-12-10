#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.02 17:02:27

void solve()
{
    int n;
    cin>>n;
    ll k;
    cin>>k;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<ll>gl(n),gr(n);
    ll g = 0;
    for(int i = 0;i < n;i++){
        g = gcd(g, a[i]);
        gl[i] = g;
    }
    g = 0;
    for(int i = n - 1;i >= 0;i--){
        g = gcd(g, a[i]);
        gr[i] = g;
    }

    for(int i = 0;i < n;i++){
        cerr<<gl[i]<<" ";
    }
    cerr<<endl;

    for(int i = 0;i < n;i++){
        cerr<<gr[i]<<" ";
    }
    cerr<<endl;

    vector<int>l,r;
    l.push_back(-1);
    r.push_back(n);
    for(int i = 0;i < n - 1;i++){
        if(gl[i] != gl[i + 1]){
            l.push_back(i);
        }
    }
    for(int i = n - 1;i > 0;i--){
        if(gr[i] != gr[i - 1]){
            r.push_back(i);
        }
    }

    auto b = a;
    for(int i = 0;i < n;i++){
        b[i] += k;
    }
    int len = __lg(n) + 1;
    vector<vector<ll>>st(n,vector<ll>(len));
    for(int i = 0;i < n;i++){
        st[i][0] = b[i];
    }
    for(int i = 1;i < len;i++){
        for(int j = 0;j + (1 << i) - 1 < n;j++){
            st[j][i] = gcd(st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
        }
    }

    auto get = [&](int l, int r)->ll
    {
        if(l > r)return 0;
        int le = r - l + 1;
        int x = __lg(le);
        return gcd(st[l][x], st[r - (1 << x) + 1][x]);
    };

    auto calc = [&](int l, int r)->ll
    {
        ll x = l >= 0 ? gl[l] : 0;
        ll y = r < n ? gr[r] : 0;
        ll g = gcd(x,y);
        g = gcd(g, get(l + 1, r - 1));
        return g;
    };  

    ll ans = gr[0];
    //if(count(a.begin(),a.end(),a[0]) == n)ans = gr[0] + k;
    for(auto x : l){
        for(auto y : r){
            if(y < x)break;
            ans = max(ans, calc(x, y));
        }
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