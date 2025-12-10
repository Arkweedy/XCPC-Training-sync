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
    auto ask = [&](int u, int v)->int
    {
        cout<<u<<" "<<v<<endl;
        int res;
        cin>>res;
        return res;
    };

    auto get = [&](auto&&self, int p, vector<int>a)->bool
    {
        map<int,vector<int>>mp;
        for(auto x : a){
            int res = ask(p, x);
            if(res == 0)return true;
            else mp[res].push_back(x);
        }
        for(auto [x, arr] : mp){
            int s = arr.back();
            arr.pop_back();
            int res = self(self, s, arr);
            if(res)return true;
        }
        return false;
    };

    vector<int>arr(n - 1);
    iota(arr.begin(),arr.end(), 2);
    get(get,1,arr);
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