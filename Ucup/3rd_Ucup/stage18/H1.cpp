#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.29 12:46:40

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>a(n, vector<int>(m));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin >> a[i][j];
        }
    }

    multiset<int>A;
    multiset<int>B;

    auto check = [&](int k)->int
    {
        vector<int>x(k),y(k);
        auto ita = prev(A.end());
        auto itb = B.begin();
        for(int i = 0;i < k;i++){
            x[i] = *ita;
            ita--;
        }
        for(int i = k - 1;i >= 0;i--){
            y[i] = *itb;
            itb++;
        }
        for(int i = 0;i < k;i++){
            if(x[i] <= y[i])return false;
        }
        return true;
    };

    auto erase = [&](int k)->void
    {
        A.clear();
        B.clear();
    };

    int sum = 0;
    for(int j = 0;j < m - 1;j++){
        for(int i = 0;i < n;i++){
            A.insert(a[i][j]);
            B.insert(a[i][j + 1]);
        }
        
        int l = 0, r = n + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            if(check(m)){
                l = m;
            }
            else{
                r = m;
            }
        }
        sum += l;
        erase(l);
    }

    if(sum >= n){
        cout << "YES" << "\n";
    }
    else{
        cout << "NO" << "\n";
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