#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.30 19:59:45

void solve()
{
    int n = 9;
    vector<int>a(10);
    ll sum = 0;
    for(int i = 1;i <= 9;i++){
        cin >> a[i];
        sum += a[i];
    }
    //guess : 0 or 1
    // 1 only if 
    int cover = 0;
    int others = 0;
    for(int i = 1;i <= 4;i++){
        //cerr << a[i] <<" " << a[10 - i] << endl;
        if(a[i] && a[10 - i]){
            cover++;
        }
        else if(a[i] || a[10 - i]){
            others = 1;
        }
    }
    if(a[5] >= 2)cover++;
    if(a[5] == 1)others = 1;
    if(a[5] * 2 - 1 > sum){
        cout << a[5] * 2 - 1 - sum << "\n";
    }
    else if(cover == 1 && !others){
        cout << 1 << "\n";
    }
    else{
        cout << 0 << "\n";
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