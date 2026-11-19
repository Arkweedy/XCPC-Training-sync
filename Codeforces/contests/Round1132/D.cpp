#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.11.06 23:43

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

void solve1()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    cerr << s << endl;
    vector<vector<int>>g(n + 1);
    int cnt = 0;
    if(count(s.begin(),s.end(), '0') == n - 1){
        g[1].push_back(2);
        g[1].push_back(3);
        g[2].push_back(3);
        cnt += 3;
        for(int i = 2;i < n - 1;i++){
            g[1].push_back(i + 2);
            cnt++;
        }
    }
    else{
        int p = 0;
        for(int i = 0;i < n - 1;i++){
            if(s[i] == '1'){
                g[1].push_back(i + 2);
                p = i + 2;
                cnt++;
            }
        }
        for(int i = 0;i < n - 1;i++){
            if(s[i] == '0'){
                g[p].push_back(i + 2);
                cnt++;
            }
            
        }
    }
    cout << cnt << endl;
    for(int i = 1;i <= n;i++){
        for(auto x : g[i]){
            cout << i << " " << x << endl;
        }
    }
    return;
}

void solve2()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>g(n);
    DSU dsu(n);
    int flg = 0;
    for(int i = 0;i < m;i++){
        int x, y;
        cin >> x >> y;
        x--, y--;
        g[x].push_back(y);
        g[y].push_back(x);
        if(!dsu.merge(x, y)){
            flg = 1;
        }
    }
    if(flg){
        string ans(n - 1, '0');
        cout << ans << endl;
        return;
    }

    vector<int>dis(n);
    vector<int>vs(n);
    queue<int>q;
    q.push(0);
    vs[0] = 1;
    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(auto x : g[p]){
            if(!vs[x]){
                vs[x] = 1;
                dis[x] = dis[p] ^ 1;
                q.push(x);
            }
        }
    }
    string ans;
    for(int i = 1;i < n;i++){
        if(dis[i] == 0)ans += '0';
        else ans += '1';
    }
    cout << ans << endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    string s;
    cin >> s;
    int tt = 1;
    cin >> tt;
    if(s == "first"){
        while(tt--){
            solve1();
        }
    }
    else{
        while(tt--){
            solve2();
        }
    }
    return 0;
}