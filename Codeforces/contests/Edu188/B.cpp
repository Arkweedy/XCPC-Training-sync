#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.16 22:39:55

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>stk;
    for(int i = n - 1;i >= 0;i--){
        while(!stk.empty() && a[i] > a[stk.back()]){
            stk.pop_back();
        }
        stk.push_back(i);
    }
    cout << stk.size() << endl;
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