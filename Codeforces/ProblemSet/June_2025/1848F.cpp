#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    if(count(a.begin(),a.end(),0) == n){
        cout<<0<<endl;
        return;
    }
    int m = n, k = 0;
    while(m != 1){
        m /= 2;
        k++;
    }
    int p = k;
    int ans = 0;
    for(int i = 0;i <= k;i++){
        int l = -1, r = p;
        auto check = [&](int x)->bool
        {
            int t = 1 << x;
            for(int i = 0;i < n - t;i++){
                if(a[i] != a[i + t])return false;
            }
            return true;
        };
        while(r - l > 1){
            int m = l + r >> 1;
            if(check(m)){
                r = m;
            }else{
                l = m;
            }
        }
        if((1 << r) == n){
            ans += p;
            p--;
            n /= 2;
            for(int i = 0;i < n;i++){
                a[i] ^= a[i + n];
            }
            a.resize(n);
            ans++;
        }else{
            ans += r + 1;
            break;
        }
    }
    cout<<ans<<endl;
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