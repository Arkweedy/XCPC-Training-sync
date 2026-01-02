#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.02 14:50:25

void solve()
{
    int n;
    cin >> n;
    map<int,vector<int>>mp;
    mp[0] = vector<int>(1);
    auto dfs = [&](auto&&self, vector<int>v, int r, int c)->void
    {
        if(!v.empty()){
            int x = v.back();
            if(x % 2 == 0){
                if(x / 2 >= 21 && x != 50){
                    ;
                }
                else{
                    mp[c] = v;
                }
            }
        }
        if(r == 3){
            return;
        }
        {
            vector<int>nv = v;
            int nc = c;
            nv.push_back(50);
            nc += 50;
            self(self, nv, r + 1, nc);
        }
        if(r != 2){
            vector<int>nv = v;
            int nc = c;
            nv.push_back(25);
            nc += 25;
            self(self, nv, r + 1, nc);
        }
        if(r != 2){
            for(int i = 1;i <= 20;i++){
                vector<int>nv = v;
                int nc = c;
                nv.push_back(i);
                nc += i;
                self(self, nv, r + 1, nc);
            }
        }
        {
            for(int i = 1;i <= 20;i++){
                vector<int>nv = v;
                int nc = c;
                nv.push_back(i * 2);
                nc += i * 2;
                self(self, nv, r + 1, nc);
            }
        }
        if(r != 2){
            for(int i = 1;i <= 20;i++){
                vector<int>nv = v;
                int nc = c;
                nv.push_back(i * 3);
                nc += i * 3;
                self(self, nv, r + 1, nc);
            }
        }
        return;
    };

    dfs(dfs, vector<int>(0), 0, 0);
    if(mp.count(n)){
        cout <<"YES" << endl;
        auto v = mp[n];
        cout << v.size() << endl;
        for(auto x : v)cout << x << " ";
        cout << endl;
    }
    else{
        cout <<"NO" << endl;
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