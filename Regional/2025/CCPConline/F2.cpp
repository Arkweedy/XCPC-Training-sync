#include<bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

constexpr int B = 100;

map<int,int>mp1;

int sg(int n)
{
    if(n == 0 || n == 1)return 0;
    if(mp1.count(n))return mp1[n];
    set<int>buf;
    for(int i=0;i<=n-2;i++){
        buf.insert(sg(i)^sg(n-2-i));
    }

    int res = 0;
    for(int i = 0;i < B;i++){
        if(!buf.count(i)){
            res = i;
            break;
        }
    }

    return mp1[n] = res;
}

void solve()
{
    int n, m;
    cin>>n>>m;
    vector<pair<int,int>>p;
    for(int i = 0;i < m;i++){
        int x, y;
        cin>>x>>y;
        p.emplace_back(x, i);
        p.emplace_back(y, i);
    }
    
    sort(p.begin(),p.end());

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<ull>ha(m);
    for(int i = 0;i < m;i++){
        ha[i] = rng();
    }
    int x = 0;
    ull h = 0;
    map<ull, int>mp;
    for(int i = 0;i < m * 2;i++){
        mp[h] += p[i].first - x;
        x = p[i].first + 1;
        h ^= ha[p[i].second];
    }
    mp[h] += n - x;
    

    constexpr int T = 136;

    int s = 0;
    for(auto [x, c] : mp){
        if(c > T){
            s ^= sg(c % 34 + T);
        }
        else{
            s ^= sg(c);
        }
    }

    cout<<(s == 0 ? "NO" : "YES")<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
