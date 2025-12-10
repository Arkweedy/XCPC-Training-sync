#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

const int N = 2e3 + 10;

ll s[N][N], r[N],c[N],t,a[N][N],n,m,f[N];

inline ll pre(int x,int y){
    ll res = s[x][y];
    if(x >= t)res -= r[y];
    if(y >= t)res -= c[x];
    if(x >= t && y <= t)res += a[t][t];
    return res;
}

inline ll ask(int x1,int y1,int x2,int y2){
    return pre(x2,y2) - pre(x2,y1-1) - pre(x1-1,y2) + pre(x1-1,y1-1);
}

void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            a[i][j] = 0;
        }
    }
    vector<int>u(m),v(m);
    
    for(int i=0;i<m;i++){
        cin>>u[i]>>v[i];
        if(u[i] > v[i])swap(u[i],v[i]);
        a[u[i]][v[i]] = u[i] + v[i];
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            s[i][j] = a[i][j] + s[i-1][j] + s[i][j-1] -s[i-1][j-1];
        }
    }

    ll res = 0;
    for(int i=1;i<=n;i++){
        t = i;
        for(int j=1;j<=n;j++){
            r[j] = r[j-1] + a[i][j];
            c[j] = c[j-1] + a[j][i];
            f[j] = 0;
        }
        ll ans = 0;
        for(int j=0;j< m;j++){
            int x = u[j],y = v[j];
            if(x == i || y == i)continue;
            ll sum = ask(x+1,y+1,y-1,n);
            sum += ask(1,x+1,x-1,y-1);
            ans += sum * (x+y);
            f[x] += sum*(x+y),f[y] += sum*(x+y);
        }
        ans/=2;
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            res = max(res,ans - f[j]);
        }
    }

    cout<<res<<'\n';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;

    while(tt--){
        solve();
    }
    return 0;
}