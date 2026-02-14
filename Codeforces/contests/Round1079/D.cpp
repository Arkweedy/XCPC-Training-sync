#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.11 22:58

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    vector<vector<int>>p(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        if(a[i] < n)p[a[i]].push_back(i);
    }
    //a_i * a_j == j - i // j > i ?
    //check i + a_i * k 
    vector<vector<int>>fac(n);
    for(int i = 1;i < n;i++){
        for(int k = 1;k * i < n;k++){
            fac[i * k].push_back(i);
        }
    }

    i64 ans = 0;
    for(int i = 1;i < n;i++){
        if(1ll * i * i <= n){
            for(int j = 0;j + i < n;j++){
                if(1ll * a[j + i] * a[j] == i)ans++;
            }
        }
        else{
            for(auto d : fac[i]){
                if(1ll * d * d >= i){
                    for(auto j : p[d]){
                        if(j + i < n && a[j + i] == i / d){
                            ans++;
                        }
                        if(1ll * d * d != i && j - i >= 0 && a[j - i] == i / d){
                            ans++;
                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;
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