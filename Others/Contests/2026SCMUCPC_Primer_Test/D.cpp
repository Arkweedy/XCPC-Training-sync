#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.05.09 19:14

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>>a(n);
    vector<int>ex(n);
    for(int i = 0;i < n;i++){
        int k;
        cin >> k;
        for(int j = 0;j < k;j++){
            int e;
            cin >> e;
            a[i].push_back(e);
        }
    }

    set<int>s;
    while(q--){
        int id;
        cin >> id;
        id--;
        if(!ex[id]){
            for(auto x : a[id]){
                s.insert(x);
            }
            ex[id] = true;
        }
        cout << s.size() << endl;
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