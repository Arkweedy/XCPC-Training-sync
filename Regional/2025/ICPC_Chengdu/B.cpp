#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.26 21:53:30

constexpr int N = 64;
using matrix = array<array<ll,N>,N>;

constexpr ll inf = 1e15;

matrix mat(ll x = -inf)
{
    matrix res{};
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            res[i][j] = -inf;
        }
    }
    for(int i = 0;i < N;i++){
        res[i][i] = x;
    }
    return res;
}

matrix operator*(const matrix& a,const matrix& b)
{
    matrix res = mat();
    for(int i = 0;i < N;i++){
        for(int k = 0;k < N;k++){
            for(int j = 0;j < N;j++){
                res[i][j] = max(res[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return res;
}

void solve()
{
    int n, m ,k, R;
    cin>>n>>m>>k>>R;
    vector<int>a(n),c(n);
    for(int i = 0;i < n;i++){
        cin>>a[i]>>c[i];
    }   
    matrix A = mat();
    int len = 1 << n;
    for(int i = 0;i < len;i++){
        for(int j = 0;j < len;j++){
            ll val = 0;
            ll cost = 0;
            for(int x = 0;x < n;x++){
                if(j >> x & 1){
                    val += a[x];
                    cost += c[x];
                    if(i >> x & 1){
                        cost += k;
                    }   
                }
            }
            if(cost <= m){
                A[i][j] = val;
            }
        }
    }

    matrix res = mat(0);
    while(R){
        if(R & 1){
            res = res * A;
        }
        A = A * A;
        R >>= 1;
    }

    ll ans = 0;
    for(int i = 0;i < len;i++){
        ans = max(ans, res[0][i]);
    }
    cout<<ans<<endl;
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