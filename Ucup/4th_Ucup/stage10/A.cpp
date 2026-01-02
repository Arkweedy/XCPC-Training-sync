#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.02 14:08:33

int add(int id){
    cout<<"+ "<<id<<endl;
    int res;cin>>res;
    return res;
}

int sub(){
    cout<<"-"<<endl;
    int res;cin>>res;
    return res;
}

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

vector<int>f;

int find(int x){
    if(f[x]!=x)f[x] = find(f[x]);
    return f[x];
}

void solve()
{
    int n;cin>>n;
    vector<int>p(n);
    f.assign(n,0);

    iota(p.begin(),p.end(),0);
    iota(f.begin(),f.end(),0);
    shuffle(p.begin(),p.end(),rng);

    int ans = n;
    deque<int>q;
    for(int i=0;i<n;i++){
        vector<int>v;
        int pre = q.size();
        q.push_back(p[i]);
        int cnt = add(p[i] + 1);
        if(cnt == pre){
            while(1){
                int j = q.front();
                v.push_back(j);
                q.pop_front();
                cnt = sub();
                if(cnt == pre)break;
                pre = cnt;    
            }
        }
        if(!v.empty()){
            ans--;
            f[find(p[i])] = find(v.back());
            v.pop_back();
            for(auto x:v)q.push_back(x),add(x + 1);
        }
    }

    vector<vector<int>>e(n);
    for(int i=0;i<n;i++)e[find(i)].push_back(i);

    cout<<"! "<<ans<<endl;

    for(int i=0;i<n;i++){
        if(e[i].empty())continue;
        cout<<e[i].size()<<' ';
        for(auto x:e[i])cout<<x+1<<' ';
        cout<<endl;
    }
}

int main()
{
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}