#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.03.14 23:09

class DSU
{
    int n;
    vector<int>fa;
    vector<int>sz;
public:
    int scc;

    DSU(int n)
    {
        this->n = n;
        scc = n;
        fa.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }

    int size(int p)
    {
        return sz[find(p)];
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            return false;
        }
        else {
            if (sz[fu] < sz[fv]) {
                swap(fu, fv);
            }
            scc--;
            sz[fu] += sz[fv];
            fa[fv] = fu;
            return true;
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    for(int i = 0;i < n;i++){
        if(a[i][i] != '1'){
            cout << "NO" << endl;
            return;
        }
    }

    vector<pair<int,int>>ans;
    vector<vector<int>>g(n);
    DSU dsu(n);
    auto calc = [&](int p)->void
    {
        string s = a[p];
        s[p] = '0';
        vector<int>t(n, -1);
        vector<int>res(n);
        for(int i = 0;i < n;i++){
            if(i == p)continue;
            int ok = 1;
            int rpc = 0;
            for(int j = 0;j < n;j++){
                if(a[i][j] == '1' && s[j] == '0'){
                    ok = 0;
                    //cerr << i << " " << j << endl;
                    break;
                }
                if(a[i][j] == '1' && s[j] == '1'){
                    if(t[j] == -1){
                        rpc = 1;
                    }
                }
            }
            if(ok && rpc){
                for(int j = 0;j < n;j++){
                    if(a[i][j] == '1'){
                        if(t[j] != -1)res[t[j]] = 0;
                        t[j] = i;
                    }
                }
                res[i] = 1;
            }
        }

        int ok2 = 1;
        for(int i = 0;i < n;i++){
            if((s[i] != '0') != (t[i] != -1)){
                ok2 = 0;
            }   
        }

        //cerr << "ans "  << p << endl;
        if(ok2){
            for(int i = 0;i < n;i++){
                if(res[i]){
                    //cerr << i << " ";
                    g[p].push_back(i);
                    ans.emplace_back(p, i);
                    dsu.merge(p, i);
                }
            }
            //cerr << endl;
        }
        return;
    };  

    for(int i = 0;i < n;i++){
        calc(i);
    }

    auto tran = [&](int x)->bool
    {
        vector<int>vs(n);
        vs[x] = 1;
        queue<int>q;
        q.push(x);
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : g[p]){
                if(!vs[s]){
                    vs[s] = 1;
                    q.push(s);
                }
            }
        }
        //cerr << "check " << x << endl;
        for(int i = 0;i < n;i++){
            //cerr << vs[i] << " " << a[x][i] << endl;
            if(a[x][i] - '0' != vs[i]){
                return false;
            }
        }
        return true;
    };

    if(ans.size() != n - 1){
        cout << "NO" << "\n";
        return;
    }

    if(dsu.scc != 1){
        cout << "NO" << "\n";
        return;
    }
    
    for(int i = 0;i < n;i++){
        if(!tran(i)){
            cout << "NO" << "\n";
            return;
        }
    }

    cout << "YES" << "\n";
    for(auto [u, v] : ans){
        cout << u + 1 << " " << v + 1 << "\n";
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