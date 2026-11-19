#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.11.07 22:40

void solve()
{
    int n;
    cin >> n;
    auto ask = [&](int l, int r)->int
    {
        cout << "? " << l << ' ' << r << endl;
        int res;
        cin >> res;
        return res;
    };

    int cnt = ask(1, n);
    if(cnt == 0 || cnt == n){
        cout << "! NO" << endl;
        return;
    }

    int pre = ask(1, cnt);
    if(pre == cnt){
        cout << "! NO" << endl;
    }
    else{
        cout << "! YES" << endl;
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