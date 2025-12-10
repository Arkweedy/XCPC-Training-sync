#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 300001;
vector<int>prime;
bitset<N + 1>isprime;

void seive()
{
    isprime.set();
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) 
            prime.push_back(i);
        
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)break;
            isprime.flip(i * p);
            if (i % p == 0)break;
        }
    }
}

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<vector<int>>g(n + N);
    vector<vector<int>>pfac(N + 1);
    for(auto p : prime){
        for(int i = 1;i * p <= N;i++){
            pfac[i * p].push_back(p);
        }
    }
    //offset ： n
    for(int i = 0;i < n;i++){
        for(auto p : pfac[a[i]]){
            g[i].push_back(p + n);
            g[p + n].push_back(i);
        }
    }

    queue<int>q;
    int s, t;
    cin>>s>>t;
    s--,t--;
    constexpr int inf = 1000;
    vector<int>dis(n + N,inf);
    vector<int>vs(n + N);
    dis[s] = 0;
    vs[s] = 1;
    q.push(s);
    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(auto x : g[p]){
            if(!vs[x]){
                vs[x] = 1;
                dis[x] = dis[p] + 1;
                q.push(x);
            }
        }
    }
    if(!vs[t]){
        cout<<-1<<endl;
    }
    else{
        cout<<dis[t] / 2 + 1<<endl;
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    seive();
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}