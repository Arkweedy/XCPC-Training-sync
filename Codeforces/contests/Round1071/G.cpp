#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using u64 = unsigned long long;

using namespace std;

//G.cpp Create time : 2025.12.24 00:44

void solve()
{
    int n;
    cin >> n;

    auto ask = [&](int x, int y)->int
    {
        cout << "? " << x + 1 << " " << y + 1 << endl;
        int res;
        cin >> res;
        return res;
    };

    vector<int>d0(n * n);
    for(int i = 0;i < n * n;i++){
        d0[i] = ask(0, i);
    }
    int p = max_element(d0.begin(),d0.end()) - d0.begin();
    vector<int>d1(n * n);
    for(int i = 0;i < n * n;i++){
        d1[i] = ask(p, i);
    }
    int q;
    int u = find(d1.begin(),d1.end(), 1) - d1.begin();
    for(int i = 0;i < n * n;i++){
        if(d1[i] == n - 1){
            if(ask(u, i) == n){
                q = i;
                break;
            }
        }
    }
    vector<int>d2(n * n);
    for(int i = 0;i < n * n;i++){
        d2[i] = ask(q, i);
    }

    vector<vector<int>>ans(n,vector<int>(n));
    //p 0,0
    //q n-1,0

    for(int i = 0;i < n * n;i++){
        int x = (d1[i] - d2[i] + n - 1) / 2;
        int y = (d1[i] + d2[i] - n + 1) / 2;
        ans[x][y] = i + 1;
    }
    
    cout << "!" << endl;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cout << ans[i][j] << " ";
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
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}