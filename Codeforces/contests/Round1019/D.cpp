#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
        if(a[i] != -1)a[i];
    }
    int m = *max_element(a.begin(),a.end());
    vector<vector<int>>g(n);//less -> greater
    vector<vector<int>>round(m);
    vector<vector<int>>ok(m);
    vector<int>indeg(n);
    for(int i = 0;i < n;i++){
        if(a[i] == -1){
            for(int j = 0;j < m;j++){
                round[j].push_back(i);
                ok[j].push_back(1);
            }
        }else{
            for(int j = 0;j < a[i];j++){
                round[j].push_back(i);
                ok[j].push_back(j != a[i] - 1);
            }
        }
    }


    auto addEdge = [&](int u, int v)->void
    {
        g[u].push_back(v);
        indeg[v]++;
    };
    
    for(int i = 0;i < m;i++){
        int len = round[i].size();
        int sta = i % 2;

        for(int j = 0;j < len;j++){
            if(ok[i][j]){
                if(sta == 0){//ok is less
                    if(j > 0)addEdge(round[i][j],round[i][j - 1]);
                    if(j < len - 1)addEdge(round[i][j],round[i][j + 1]);
                }else{
                    if(j > 0)addEdge(round[i][j - 1],round[i][j]);
                    if(j < len - 1)addEdge(round[i][j + 1],round[i][j]);
                }
            }
        }
        int j = 0;
        while(ok[i][j] == 0){
            if(j + 1 < len){
                if(sta == 0)addEdge(round[i][j + 1],round[i][j]);
                else addEdge(round[i][j],round[i][j + 1]);
            }else break;
            j++;
        }
        j = len - 1;
        while(ok[i][j] == 0){
            if(j > 0){
                if(sta == 0)addEdge(round[i][j - 1],round[i][j]);
                else addEdge(round[i][j],round[i][j - 1]);
            }else break;
            j--;
        }
    }
    
    vector<int>rnk;
    int pr = 0;
    for(int i = 0;i < n;i++){
        if(indeg[i] == 0){
            rnk.push_back(i);
        }
    }
    
    
    while(pr != n){
        int p = rnk[pr++];
        for(auto s : g[p]){
            indeg[s]--;
            if(indeg[s] == 0)rnk.push_back(s);
        }
    }

    vector<int>ans(n);
    for(int i = 0;i < n;i++){
        ans[rnk[i]] = i;
    }
    for(int i  =0;i < n;i++){
        cout<<ans[i] + 1<<" ";
    }
    cout<<endl;
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