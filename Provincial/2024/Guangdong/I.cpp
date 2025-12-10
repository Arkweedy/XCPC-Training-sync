#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.29 16:04:44

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>in(n);
    vector<vector<pair<int,int>>>e(n);
    for(int i = 0;i < m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        a--,b--,c--;
        e[b].emplace_back(c, a);
        e[c].emplace_back(b, a);
        in[a] += 2;
    }   

    queue<int>q;
    for(int i = 0;i < n;i++){
        if(!in[i])q.push(i);
    }

    vector<int>vs(n);
    vector<ll>val(n, 1);
    while(!q.empty()){
        int p = q.front();
        q.pop();
        vs[p] = 1;
        for(auto [x, y] : e[p]){
            if(vs[x]){
                val[y] = max(val[y], val[p] + val[x]);
                in[y] -= 2;
                if(in[y] == 0)q.push(y);
            }
        }
    }

    int c = count(vs.begin(),vs.end(), 0);
    if(c != 0){
        cout<<-1<<endl;
        return;
    }

    ll ans = 0;
    constexpr int inf = 1e9;
    for(int i = 0;i < n;i++){
        ans += val[i];
    }
    if(ans <= inf){
        cout<<ans<<endl;
    }
    else{
        cout<<-1<<endl;
    }
    
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