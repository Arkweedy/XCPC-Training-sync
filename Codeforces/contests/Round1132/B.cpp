#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.11.06 22:43

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    int mi = count(a.begin(),a.end(), a.back());
    if(k < mi){
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    for(int i = n - k;i < n;i++){
        cout << a[i] << " ";
    }
    for(int i = n - k - 1;i >= 0;i--){
        cout << a[i] << " ";
    }
    cout << endl;
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