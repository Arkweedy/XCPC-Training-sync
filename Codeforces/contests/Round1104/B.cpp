#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.06.18 22:46

void solve()
{
    int n;
    cin >> n;
    vector<i64>a(n), b(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
    }
    for(int i = 0;i < n;i++){
        a[i] = lower_bound(b.begin(),b.end(), a[i]) - b.begin();
    }
    i64 ans = 0;
    for(int i = 0;i < n;i++){
        for(int j = i;j < n;j++){
            if(a[j] <= i){
                for(int k = j - 1; k >= i;k--){
                    swap(a[k], a[k + 1]);
                    ans++;
                }
                break;
            }
        }
        if(a[i] > i){
            ans = -1;
            break;
        }
    }

    cout << ans << endl;
    return;
    // make a_i <= i
    // for(int i = 0;i < n;i++){
    //     a[i] -= i;
    // }
    // vector<i64>pa = a;
    // for(int i = 1;i < n;i++){
    //     pa[i] += pa[i - 1];
    // }
    // i64 ans = 0;
    // for(int i = 0; i < n;i++){
    //     cerr << pa[i] << " ";
    //     if(pa[i] > 0)ans += pa[i];
    // }
    // cerr << endl;
    // if(pa[n - 1] > 0)ans = -1;
    // cout << ans << endl;
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