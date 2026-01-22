#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.20 10:35:36
int k=13;
void solve()
{
    int n = 50;
    int cnt = 0;
    int x = 25, y = 25;
    for(int i = 0;i <= n;i++){
        for(int j = 0;i + j <= n;j++){
            for(int k = 0;k + i <= n;k++){
                for(int t = 0;j + t <= n && k + t <= n;t++){
                    cnt+=i*i;
                }
            }
        }
    }
    cout << cnt << endl;
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