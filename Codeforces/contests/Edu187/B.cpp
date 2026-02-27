#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.25 22:39

int digit(i64 a)
{
    int res = 0;
    while(a){
        res += a % 10;
        a /= 10;
    }
    return res;
}

void solve()
{
    i64 a;
    cin >> a;
    vector<int>b;
    int sum = 0;
    while(a >= 10){
        b.push_back(a % 10);
        sum += a % 10;
        a /= 10;
    }
    sum += a;
    b.push_back(a - 1);
    //cerr << sum << endl;
    sort(b.begin(),b.end(), greater<>());
    int ans = 0;
    for(int i = 0;i < b.size();i++){
        if(sum < 10){
            ans = i;
            break;
        }
        sum -= b[i];
        // if(sum < 10){
        //     ans = i + 1;
        //     break;
        // }
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