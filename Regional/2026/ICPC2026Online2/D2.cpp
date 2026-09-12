#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;
using namespace std;

constexpr int P = 998244353;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    int ok = 1;
    const int M = 1 << n + 1;
    const int N = 1 << n;
    vector<int>a(M, -1);
    vector<int>ex(N + 1);
    for(int i = 0;i < q;i++){
        int p, v;
        cin >> p >> v;
        ex[v] = 1;
        if(a[p] != -1){
            if(a[p] != v)ok = 0;
        }
        else{
            a[p] = v;
        }
    }

    vector<vector<int>>pos(N + 1);
    for(int i = 1;i < M;i++){
        if(a[i] != -1){
            pos[a[i]].push_back(i);
        }
    }
    for(int i = 1;i <= N;i++){
        if(!pos[i].empty()){
            int x = pos[i].back();
            pos[i].pop_back();
            while(!pos[i].empty()){
                x /= 2;
                if(x == pos[i].back())pos[i].pop_back();
                else if(x < pos[i].back()){
                    ok = 0;
                    break;
                }
            }
        }
    }


    auto dfs1 = [&](auto&&self, int p, int dep)->void
    {
        if(dep == n)return;
        self(self, p * 2, dep + 1);
        self(self, p * 2 + 1, dep + 1);
        if(a[p] == -1){
            if(a[p * 2] != -1 && a[p * 2 + 1] != -1){
                a[p] = max(a[p * 2], a[p * 2 + 1]);
            }
            //
        }
        else{
            if(max(a[p * 2], a[p * 2 + 1]) == -1){
                //
            }
            else{
                if(a[p] != max(a[p * 2], a[p * 2 + 1])){
                    if(a[p * 2] == -1 || a[p * 2 + 1] == -1){
                        if(a[p * 2] > a[p] || a[p * 2 + 1] > a[p]){
                            ok = 0;
                        }
                        else{
                            //
                        }
                    }
                    else{
                        ok = 0;
                    }
                }
                else{
                    //
                }
            }   
        }
    };
    dfs1(dfs1, 1, 0);

    // for(int i = 1;i < M;i++){
    //     cerr << a[i] << " ";
    // }
    // cerr << endl;
    

    if(a[1] == -1){
        a[1] = N;
    }
    if(a[1] != N){
        ok = 0;
    }
    
    if(!ok){
        cout << 0 << endl;
        return;
    }

    // for(int i = 1;i < M;i++){
    //     cerr << a[i] << " ";
    // }
    // cerr << endl;

    auto dfs2 = [&](auto&&self, int p, int dep)->void
    {
        if(dep == n)return;
        
        if(a[p] == max(a[p * 2], a[p * 2 + 1])){
            if(a[p * 2] == a[p] && a[p * 2 + 1] == a[p]){
                ok = 0;
            }
            else if(a[p] == a[p * 2]){
                if(a[p * 2 + 1] == -1){
                    a[p * 2 + 1] = a[p] - 1;
                }
            }
            else if(a[p] == a[p * 2 + 1]){
                if(a[p * 2] == -1){
                    a[p * 2] = a[p] - 1;
                }
            }
        }
        else{
            if(a[p * 2] == -1)a[p * 2] = a[p];
            else if(a[p * 2] > a[p])ok = 0;
            if(a[p * 2 + 1] == -1)a[p * 2 + 1] = a[p];
            else if(a[p * 2 + 1] > a[p])ok = 0;

            // if(a[p * 2] == -1 && a[p * 2 + 1] == -1 && a[p] == n){
            //     a[p * 2] = a[p * 2 + 1] = n;
            // }
            // else{
            //     cerr << "#" << p << endl;
            //     assert(0);
            // }
        }
        self(self, p * 2, dep + 1);
        self(self, p * 2 + 1, dep + 1);
    };
    dfs2(dfs2, 1, 0);

    // for(int i = 1;i < M;i++){
    //     cerr << a[i] << " ";
    // }
    // cerr << endl;



    if(ok == 0){
        cout << 0 << endl;
        return;
    }

    
    vector<int>cnt(N + 1);
    for(int i = N;i < M;i++){
        cnt[a[i]]++;
    }

    
    vector<int>fac(N + 1), invfac(N + 1);
    fac[0] = 1;
    for(int i = 1;i <= N;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[N] = power(fac[N], P - 2);
    for(int i = N - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    // for(int i = 0;i <= N;i++){
    //     cerr << fac[i] << " " << invfac[i] << endl;
    // }

    auto binom = [&](int n, int m)->int
    {
        if(n < 0 || m < 0 || n < m)return 0;
        //cerr << "A" << n << " " << m << endl;
        return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
    };

    for(int i = 1;i <= (1 << n);i++){
        cerr << cnt[i] << " ";
    }
    cerr << endl;

    int rem = 0;
    int ans = 1;
    for(int i = 1;i <= N;i++){
        cerr << "#" << endl;
        rem++;
        if(cnt[i] <= rem){
            if(cnt[i] == 0)continue;
            if(ex[i]){
                ans = 1ll * ans * binom(rem - 1, cnt[i] - 1) % P * fac[cnt[i]] % P;
            }
            else{
                ans = 1ll * ans * binom(rem, cnt[i]) % P * fac[cnt[i]] % P;
            }
            rem -= cnt[i];
        }
        else{
            ans = 0;
            break;
        }
    }
    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}



