#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using ld = long double;
using namespace std;

//K.cpp Create time : 2026.04.07 18:17

int n = 300,m = 0,tot = 2;

ld ans;
vector<pair<int,int>>res;



void dfs(int u,ld s,int op){
    if(s < 1e-7)return;
    if(s<1){
        dfs(u,1/s,op^1);
        ans = 1 / ans;
        return;
    }
    if(op==0){
        res.push_back({u,tot});
        tot++;
        if(tot > n){
            return;
        }
        else if(res.size()<299){
            dfs(tot - 1,s-1,op);
            ans+=1;
        }
        else {
            res.push_back({tot - 1,n});
            ans+=1;
        }
    }else{
        res.push_back({u,n});
        if(res.size()<299){
            dfs(u,s-1,op);
            ans+=1;
        }
        else{
            res.push_back({u,n});
            ans+=1;
        }
    }
}

void solve()
{
    int d;cin>>d;
    dfs(1,sqrtl(d),0);
    cout<<tot-1<<' '<<res.size()<<'\n';
    assert(tot -1<= 300);
    assert(res.size() <= 300);
    for(auto [u,v]:res){
        u = min(u,tot-1);
        v = min(v,tot-1);
        cout<<u<<' '<<v<<'\n';
    }
    // cout<<fixed<<setprecision(10);
    // cout<<abs(ans-sqrtl(d))<<endl;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}