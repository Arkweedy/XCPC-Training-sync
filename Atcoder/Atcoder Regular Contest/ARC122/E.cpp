#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.17 16:12

void solve()
{
    int n;
    cin >> n;
    vector<i64>a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    //some con
    vector<i64>ans;
    for(int k = n - 1;k >= 0;k--){
        int ok = 0;
        int p = -1;
        for(int i = 0;i <= k;i++){
            i64 glc = 1;
            for(int j = 0;j <= k;j++){
                if(i == j)continue;
                glc = lcm(glc, gcd(a[i], a[j]));
                if(glc >= a[i])break;
            }
            if(glc < a[i]){
                ok = 1;
                p = i;
                break;
            }
        }
        if(ok){
            ans.push_back(a[p]);
            a.erase(a.begin() + p);
        }
        else{
            cout << "No" << endl;
            return;
        }
        
    }
    reverse(ans.begin(), ans.end());
    cout << "Yes" << endl;
    for(int i = 0;i < n;i++){
        cout << ans[i] << " ";
    }
    cout << endl;
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