#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>a(n + 1);
    string s;
    cin>>s;
    s = '0' + s;
    for(int i = 1;i <= n;i++){
        a[i] = s[i] ^ s[i - 1]; 
    }

    while(q--){
        int op;
        cin>>op;
        if(op == 1){
            int l, r;
            cin>>l>>r;
            a[l] ^= 1;
            a[r + 1] ^= 1; 
        }
        else{
            int l, x, y;
            cin>>l>>x>>y;
            int pa = 0, pb = 0;
            if(x > y)swap(x, y);
            for(int i = x;i < y;i++){
                pb ^= a[i];
            }
            ll ans = 0;
            int cnt = 0;
            for(int i = 0;i < l;i++){
                if((pa ^= a[x + i]) == (pb ^= a[y + i]))ans += ++cnt;
                else cnt = 0;
            }
            cout<<ans<<'\n';
        }
    }
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