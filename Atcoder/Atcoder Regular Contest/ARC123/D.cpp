#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.03.03 17:06

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    auto calc = [&]()->i64
    {
        vector<i64>b(n), c(n);
        if(a[0] > 0)c[0] = a[0];
        else b[0] = a[0];
        for(int i = 1;i < n;i++){
            if(a[i] >= a[i - 1]){
                b[i] = b[i - 1] + a[i] - a[i - 1];
                c[i] = c[i - 1];
            }
            else{
                b[i] = b[i - 1];
                c[i] = c[i - 1] + a[i] - a[i - 1];
            }
        }

        i64 ans = 0;
        for(int i = 0;i < n;i++){
            ans += abs(b[i]);
            ans += abs(c[i]);
        }
        for(int i = 0;i < n;i++){
            cerr << b[i] << " ";
        }
        cerr << endl;
        for(int i = 0;i < n;i++){
            cerr << c[i] << " ";
        }
        cerr << endl;
        cout << ans << endl;
        return ans;
    };
    calc();
    reverse(a.begin(),a.end());
    calc();
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