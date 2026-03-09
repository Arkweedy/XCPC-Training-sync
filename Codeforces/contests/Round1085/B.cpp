#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.08 22:45:27

void solve()
{
    int n, m, l;
    cin >> n >> m >> l;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    a.push_back(l);
    n++;
    
    int ans = 0;
    int sum = 0;

    for(int i = 1;i <= n;i++){
        sum += a[i] - a[i - 1];
        int ave = (sum + m - 1) / m;
        cerr << sum << " " << ave << endl;
        if(i != n){
            sum -= ave;
        }
        else{
            ans =
        }
    }
    cout << sum << endl;
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