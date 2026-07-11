#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.06.18 23:24

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int>a(n), b(n);
    for(int i = 0;i < n;i++){
        a[i] = s[i] - '0';
        if(a[i] == 1)b[i] = 1;
        else b[i] = 2;
        if(i % 2 == 1)a[i] ^= 1;

    }

    // force
    auto check = [&](int l, int r)->int
    {
        int len = r - l + 1;
        if(len == 1)return 0;
        if(count(a.begin() + l,a.begin() + r + 1, 0) == len || (count(a.begin() + l,a.begin() + r + 1, 1) == len))return 1;
        int sum = 0;
        for(int i = l;i <= r;i++){
            if((a[i] + i) % 2 == 0)sum += 1;
            else sum += 2;
        }
        if(sum % 3 == 0)return 1;
        else return 0;
    };

    i64 res = 0;
    for(int i = 0;i < n;i++){
        for(int j = i;j < n;j++){
            if(check(i, j)){
                res++;
            }
            else{
                //cerr << i + 1 << " "  << j + 1 << " is ok" << endl;
            }
        }
    }

    i64 ans = 1ll * n * (n + 1) / 2 - res;
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