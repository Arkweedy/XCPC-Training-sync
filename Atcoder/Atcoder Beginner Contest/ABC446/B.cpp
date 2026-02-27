#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.21 20:03

void solve()
{
    int  n, m;
    cin >> n >> m;
    vector<int>vs(m + 1);
    for(int i = 0;i < n;i++){
        int k;
        cin >> k;
        vector<int>a(k);
        for(int i = 0;i < k;i++){
            cin >> a[i];
        }
        int ok = 1;
        for(int i = 0;i < k;i++){
            if(!vs[a[i]]){
                cout << a[i] << "\n";
                ok = 0;
                vs[a[i]] = 1;
                break;
            }
        }
        if(ok){
            cout << 0 << "\n";
        }
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