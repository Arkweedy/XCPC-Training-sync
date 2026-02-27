#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.02.26 22:33

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    vector<int>pos(n + 1);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        pos[a[i]] = i;
    }
    swap(a[pos[n]], a[0]);
    for(int i = 0;i < n;i++){
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