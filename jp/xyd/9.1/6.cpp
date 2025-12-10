#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 19650827;

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<int>dpl(n, 1);
    vector<int>dpr(n, 0);
    for(int i = 2;i <= n;i++){
        vector<int>ndpl(n);
        vector<int>ndpr(n);
        for(int j = 0;i + j - 1 < n;j++){
            // [j, i + j - 1]
            //add l
            if(a[j + 1] > a[j]){
                ndpl[j] += dpl[j + 1];
                ndpl[j] %= P;
            }
            if(a[i + j - 1] > a[j]){
                ndpl[j] += dpr[j + 1];
                ndpl[j] %= P;
            }

            //add r
            if(a[j] < a[i + j - 1]){
                ndpr[j] += dpl[j];
                ndpr[j] %= P;
            }
            if(a[i + j - 2] < a[i + j - 1]){
                ndpr[j] += dpr[j];
                ndpr[j] %= P;
            }
        }
        dpl = move(ndpl);
        dpr = move(ndpr);
    }
    cout<<(dpl[0] + dpr[0]) % P<<endl;
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