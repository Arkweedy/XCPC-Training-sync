#include<bits/stdc++.h>
using ll = long long;
using namespace std;

constexpr int N = 1e5;

void solve()
{
    int n,a,b,c;
    cin>>n>>a>>b>>c;

    ll sum = 1ll * n * (a + b + c);
    //cerr<<sum<<endl;
    //nc + x(a - c) + y(b - c)
    int d = a - c, e = b - c;
    ll ans = 1e9;
    array<int,3>chs = {0,0,0};
    for(int i = 0;i <= n;i++){
        int l = 0, r = n - i + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            ll res = 1ll * n * c + 1ll * i * d + 1ll * m * e;
            if(e > 0){
                if(res * 3 > sum){
                    r = m;
                }
                else{
                    l = m;
                }
            }
            else{
                if(res * 3 < sum){
                    r = m;
                }
                else{
                    l = m;
                }
            }
        }
        // l, l + 1
        ll dif1 = abs(sum - 3 * (1ll * n * c + 1ll * i * d + 1ll * l * e));
        if(dif1 < ans){
            ans = dif1;
            chs = {i,l,n-i-l};
        }
        ll dif2 = abs(sum - 3 * (1ll * n * c + 1ll * i * d + 1ll * (l + 1) * e));
        if(dif2 < ans && i + l + 1 <= n){
            ans = dif2;
            chs = {i,l + 1,n - i - l - 1};
        }
    }

    auto output = [&](int x)->void
    {
        cout<<x<<endl;
        int y,z;
        cin>>y>>z;
        return;
    };

    array<int,3>val = {a,b,c};

    for(int i = 0;i < 3;i++){
        for(int j = 0;j < chs[i];j++){
            output(val[i]);
        }
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while (tt--)
    {
        solve();
    }
    return 0;    
}
