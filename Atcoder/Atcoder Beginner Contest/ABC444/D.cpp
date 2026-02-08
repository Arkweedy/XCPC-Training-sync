#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.07 20:17

void solve()
{
    int n;
    cin >> n;
    constexpr int N = 2e5 + 3e4;
    vector<int>c(N);
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        c[x]++;
    }
    for(int i = N - 2;i >= 1;i--){
        c[i] += c[i + 1];
    }

    for(int i = 1;i <= N - 1;i++){
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

    int up = N - 1;
    while(up != 1 && c[up] == 0)up--;
    for(int i = up;i >= 1;i--){
        cout << c[i];
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