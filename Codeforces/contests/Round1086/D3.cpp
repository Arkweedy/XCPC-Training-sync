#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D3.cpp Create time : 2026.03.15 00:17

void solve()
{
    int n;
    cin >> n;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    queue<int>q;
    for(int i = 0;i < n;i++){
        if(count(a[i].begin(),a[i].end(), '1') == 1){
            q.push(i);
        }
    }


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