#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.30 21:26:37

void solve()
{
    array<int,3>a,id;
    cin >> a[0] >> a[1] >> a[2];
    iota(id.begin(),id.end(), 0);
    sort(id.begin(),id.end(), [&](int i, int j)->bool
    {
        return a[i] < a[j];        
    });
    array<int,3>rk;
    for(int i = 0;i < 3;i++){
        rk[id[i]] = i;
    }
    array<vector<int>, 3>ans;
    int c0 = a[id[0]], c1 = a[id[1]], c2 = a[id[2]];
    if(c0 == c1){//0
        ans[0].resize(c0, 0);
        ans[1].resize(c2, 0);
        ans[2].resize(c2, 0);
    }
    else {//01
        //000001|111111
        //000001|000000
        //111111|000000
        for(int i = 0;i < c0 - 1;i++){
            ans[0].push_back(0);
            ans[1].push_back(0);
        }
        ans[1].push_back(1);
        for(int i = 0;i < c1;i++){
            ans[0].push_back(1);
            ans[2].push_back(1);
        }
        for(int i = 0;i < c2 - 1;i++){
            ans[1].push_back(0);
            ans[2].push_back(0);
        }
    }

    for(int i = 0;i < 3;i++){
        cout << ans[rk[i]].size() << " ";
        for(int j = 0;j < ans[rk[i]].size();j++){
            cout << ans[rk[i]][j] << " ";
        }
        cout << endl;
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