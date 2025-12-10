#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    constexpr int N = 10, M = 5;
    vector<int>a(N);
    iota(a.begin(),a.end(), 1);
    queue<vector<int>>q;
    map<vector<int>,int>vs;
    vs[a] = 1;
    q.push(a);
    auto shift = [&](vector<int>a, int i)->vector<int>
    {
        auto b = a;
        for(int j = 0;j < M;j++){
            b[i + j] = a[(j + 1) % M + i]; 
        }
        return b;
    };
    // auto t = shift(a,N - M - 1);
    // for(int i = 0;i < N;i++){
    //     cerr<<t[i]<<" ";
    // }
    // cerr<<endl;
    while(!q.empty()){
        auto vec = q.front();
        q.pop();
        for(int i = 0;i < N - M + 1;i++){
            auto b = shift(vec,i);
            if(!vs[b]){
                vs[b] = 1;
                q.push(b);
            }
        }
    }
    cout<<10*9*8*7*6*5*4*3<<endl;
    cout<<vs.size()<<endl;
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