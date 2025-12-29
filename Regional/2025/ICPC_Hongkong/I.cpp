#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.29 15:09:44

std::mt19937_64 rng(std::chrono::steady_clock().now().time_since_epoch().count());

const int N = 510,mod = 1e9 + 7;

ull ha[N],val[N][N];
int p[N][N],a[N][N];
int n,st[N][N],m;
ll f[N][N],g[N][N];

ull get(int i,int l,int r){
    return val[i][r] ^ val[i][l-1];
}

void solve()
{
    cin>>n>>m;

    for(int i=0;i<=n + 1;i++){
        for(int j=0;j <= n + 1;j++){
            f[i][j] = g[i][j] = 1;
        }
    }

    for(int i=1;i<=n;i++){
        ha[i] = rng();
    }

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            p[i][a[i][j]] = j;
            val[i][j] = ha[a[i][j]] ^ val[i][j-1];
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            st[i][j] = 1;
            for(int k=2;k<=m;k++){
                int L = p[k][a[1][i]];
                int R = L + j - i;
                if(R > n || get(1,i,j) != get(k,L,R))st[i][j] = 0;
            }
        }
    }

    for(int len=2;len<=n;len++){
        for(int L=1;L+len-1<=n;L++){
            int R = L + len - 1;
            f[L][R] = g[L][R] = 0;
            for(int k=L+1;k<=R;k++){
                // [L+1,k]
                f[L][R] = (f[L][R] + f[L+1][k] * g[k+1][R]) % mod;
            }
            f[L][R] *= st[L][R];
            for(int k=L;k<=R;k++){
                // [L,k]
                g[L][R] = (g[L][R] + f[L][k] * g[k+1][R]) % mod;
            }
        }
    }

    cout<<f[1][n]<<'\n';
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