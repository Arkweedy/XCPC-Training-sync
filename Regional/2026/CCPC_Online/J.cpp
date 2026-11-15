#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    i64 sum = 0;
    int ama = 0;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i];
        ama = max(ama, a[i]);
    }
    vector<int>b = a;
    b.reserve(n * 2);
    for(int i = 0;i < n;i++){
        b.push_back(a[i]);
    }

    

    auto check = [&](i64 ma)->bool
    {
        if(sum <= ma)return true;
        if(ama > ma)return false;
        vector<int>ne(n);
        int p = 0;
        i64 s = 0;
        for(int i = 0;i < n;i++){
            while(p < n * 2 && s + b[p] <= ma){
                s += b[p];
                p++;
            }
            ne[i] = (p >= n ? p - n : p);
            s -= b[i];
        }
        vector<vector<int>>g(n);
        for(int i = 0;i < n;i++){
            g[ne[i]].push_back(i);
        }

        vector<int>vs1(n);
        auto dfs1 = [&](auto&&self, int p)->int
        {
            if(vs1[p])return p;
            vs1[p] = 1;
            return self(self, ne[p]);
        };

        auto w = [&](int u, int v)->int
        {
            if(u > v)return u - v;
            else return u + n - v;
        };

        vector<int>oncir(n);
        vector<int>vs2(n);
        for(int i = 0;i < n;i++){
            if(!vs1[i]){
                int rt = dfs1(dfs1, i);
                oncir[rt] = 1;
                int circnt = 1;
                int pp = rt;
                do{
                    pp = ne[pp];
                    oncir[pp] = 1;
                    circnt++;
                }while(pp != rt);

                if(circnt <= k){
                    auto dfs3 = [&](auto&&self, int p)->void
                    {
                        vs1[p] = 1;
                        if(vs2[p])return;
                        vs2[p] = 1;
                        for(auto s : g[p]){
                            self(self, s);
                        }
                    };
                    dfs3(dfs3, rt);
                    return true;
                }

                vector<i64>dis;
                
                pp = rt;
                i64 d = 0;
                vector<int>stk;
                stk.push_back(rt);
                for(int i = 0;i < k;i++){
                    pp = ne[pp];
                    stk.push_back(pp);
                }
                for(int i = k;i >= 1;i--){
                    dis.push_back(d);
                    d += w(stk[i], stk[i - 1]);
                }
                dis.push_back(d);
                
                int ok = 0;
                
                auto dfs2 = [&](auto&&self, int p)->void
                {
                    vs1[p] = 1;
                    if(vs2[p])return;
                    vs2[p] = 1;

                    int la = dis.size() - 1;
                    if(dis[la] - dis[la - k] >= n){
                        ok = 1;
                    }

                    int cirp = -1;
                    for(auto s : g[p]){
                        if(!oncir[s]){
                            d += w(p, s);
                            dis.push_back(d);
                            self(self, s);
                            d -= w(p, s);
                            dis.pop_back();
                        }
                        else{
                            cirp = s;
                        }
                    }
                    if(cirp != -1){
                        d += w(p, cirp);
                        dis.push_back(d);
                        self(self, cirp);
                        d -= w(p, cirp);
                        dis.pop_back();
                    }

                    return;
                };
                dfs2(dfs2, rt);
                
                if(ok)return true;
            }
        }
        return false;
    };

    // l = max(0, sum / k - 1)
    i64 l = max(0ll, sum / k - 1), r = sum;
    while(r - l > 1){
        i64 mid = l + r >> 1;
        if(check(mid)){
            r = mid;
        }
        else{
            l = mid;
        }
    }
    i64 ans = r * (m - 1) + sum;
    cout << ans << endl;
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

