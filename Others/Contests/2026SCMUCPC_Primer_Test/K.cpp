#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//K.cpp Create time : 2026.05.09 20:51

void solve()
{
    int n;
    cin >> n;
    cout << n - 1 << endl;
    for(int i = 0;i < n - 1;i++){
        cout << fixed << setprecision(10) << (long double)180 * i / n << endl;
    }

    int tot = 1;
    
    
    if(n >= 2)cout << 1 << " " << n * 2 - 2 << endl;
    else cout << 1 << ' ' << 1 << endl;
    if(n >= 2)cout << 1 << " " << n - 1 << endl;
    if(n >= 3){
        vector<int>used(n * 2);
        used[n * 2 - 2] = used[n - 1] = 1;
        int p = 1;
        for(int i = 3;i <= n;i++){
            int c = 0;
            cout << 2 << " ";
            while(c < 2){
                if(used[p])p++;
                cout << p++ << " ";
                c++;
            }
            cout << endl;
        }
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