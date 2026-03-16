#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.03.14 23:09

void solve()
{
    int n;
    cin >> n;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<u64>v(n);
    map<u64, int>mp;
    for(int i = 0;i < n;i++){
        //v[i] = rng();
        v[i] = 1 << i;
        mp[v[i]] = i;
    }

    vector<u64>col(n);
    vector<int>c(n);
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(a[j][i] == '1'){
                col[i] ^= v[j];
                c[i]++;
            }
        }
    }

    for(int i = 0;i < n;i++){
        cerr << col[i] << " ";
    }
    cerr << endl;

    vector<pair<int,int>>ans;

    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            u64 h = col[i] ^ col[j];
            if(mp.count(h)){
                if(c[i] < c[j]){
                    ans.emplace_back(j, i);
                }
                else{
                    ans.emplace_back(i, j);
                }
            }
        }
    }

    if(ans.size() != n - 1){
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << "\n";
    for(auto [u, v] : ans){
        cout << u + 1 << " " << v + 1 << "\n";
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