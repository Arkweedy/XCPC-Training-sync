#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.10.11 00:56:14

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>c(n + 1);
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        c[x]++;
    }

    
    
    auto check = [&](int x)->bool
    {
        if(x < n)return false;
        x -= (x - n) & 1;
        auto nc = c;
        
        int p = x;
        int v = k + x - 1;
        for(int i = n;i > 0;i--){
            while(c[i] > 0){
                if(p == 0){
                    c = move(nc);
                    return false;
                }
                if(v < i){
                    c[(i + 1) / 2] += 2;
                }
                else{
                    v--;
                }
                c[i]--;
                p--;
            }
        }
        c = move(nc);
        if(p == 1)return false;
        return true;
    };

    int l = 0, r = 3 * n + 1;
    while(r - l > 1){
        int m = l + r >> 1;
        if(check(m)){
            r = m;
        }
        else{
            l = m;
        }
    }
    cout << r << endl;
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