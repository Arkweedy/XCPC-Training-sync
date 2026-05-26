#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//I.cpp Create time : 2026.05.09 20:27

// update : 最好在题目描述区域也提及一下a的值域，这个可以在cf找些例子？

// 1. [0]
// 2. [0, 1, 1, ...] 
// 3. [0, -1, -1, ...]
// 4. [1, -1]
// 5. [-1, 1]

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    i64 ans = 0;
    int fp = 0, fn = 0;
    for(int i = 0;i < n;i++){
        if(a[i] == 0) {
            ans++;
            fp = fn = 1;
        }
        else if(a[i] == 1){
            if(fp)ans++;
            if(fn)fn = 0;
        }
        else if(a[i] == -1){
            if(fp)fp = 0;
            if(fn)ans++;
        }
    }
    for(int i = 0;i < n - 1;i++){
        if(a[i] == 1 && a[i + 1] == -1)ans++;
        if(a[i] == -1 && a[i + 1] == 1)ans++;
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