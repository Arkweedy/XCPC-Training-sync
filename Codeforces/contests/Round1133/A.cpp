#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.11.07 22:29

void solve()
{
    int n, k;
    cin >> n >> k;
    int a = 0, b = 0;
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        if(x % 2 == 1)a++;
    }
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        if(x % 2 == 1)b++;
    }

    if((k % 2 == 1 && a <= b) || (k % 2 == 0 && a >= b)){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
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