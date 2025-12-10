#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.30 11:22:28

void solve()
{
    int n = 4;
    vector<vector<int>>a(n + 1);
    vector<int>b;
    a[0].push_back(0);
    for(int i = 1;i <= n;i++){
        for(auto x : a[i - 1]){
            for(int j = 1;j <= 3;j++){
                a[i].push_back(x * 10 + j);
                b.push_back(x * 10 + j);
            }
        }
    }
    
    constexpr int N = 1e4;
    vector<int>dis(N + 1);
    vector<int>vs(N + 1);
    queue<int>q;
    q.push(0);
    vs[0] = 1;
    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(auto x : b){
            int y = p + x;
            if(y <= N && !vs[y]){
                dis[y] = dis[p] + 1;
                vs[y] = true;
                q.push(y);
            }
        }
    }

    ofstream fout("C.log");
    for(int i = 1;i <= N;i++){
        fout<<i<<" "<<i % 999<<" "<<dis[i]<<endl;
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