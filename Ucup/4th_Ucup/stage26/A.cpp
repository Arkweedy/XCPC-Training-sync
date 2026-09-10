#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const int N = 1e5 + 9;
int fa[N];
int a[N];
int b[N];
int n,m;
vector<int> adj[N];
bool mark[N];

int fin(int u)
{
    if(u != fa[u]) fa[u] = fin(fa[u]);
    return fa[u];
}
void dfs(const int p,const int f)
{
    if(mark[p])
    {
        for(const int u : adj[p])
        {
            if(adj[u].size() == 1)
            {
                fa[u] = p;
            }
        }
        
        return;
    }
    for(const int u : adj[p])
    {
        if(u == f) continue;
        dfs(u,p);
    }
    if(b[p] != 0)
    {
        for(const int u : adj[p])
        {
            if(u == f) continue;
            if(b[u] == 0)
            {
                b[u] = b[p];
            }
        }
    }
    else
    {
        for(const int u : adj[p])
        {
            if(u == f) continue;
            if(b[u] == 0)
            {
                fa[fin(u)] = p;
            }
        }
    }

}
int cnt[N];
bool ck()
{
    for(int i = 1;i<=n;i++)
    {
        int cntt = 0;
        for(const int u : adj[i])
        {
            if(b[u] == b[i]) cntt++;
        }
        for(const int u : adj[i])
        {
            cnt[b[u]]++;
            if(cnt[b[u]] > cntt) return false;
        }
        for(const int u : adj[i])
        {
            cnt[b[u]]--;
        }
    }
    return true;
}
void solve()
{
    cin >> n >> m;
    for(int i = 1;i<=n;i++)
    {
        fa[i] = i;
        b[i] = 0;
        mark[i] = false;
        adj[i].clear();
        cnt[i] = 0;
    }

    for(int i = 1;i<=m;i++)
    {
        cin >> a[i];
        b[a[i]] = i;
    }
    for(int i = 1;i<=n-1;i++)
    {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 1;i<=n;i++)
    {
        if(adj[i].size() == 1)
        {
            mark[adj[i][0]] = true;
        }
    }

    for(int i = 1;i<=n;i++)
    {
        if(mark[i])
        {
            int num = 0;
            if(b[i]) num = b[i];
            for(const int u : adj[i])
            {
                if(adj[u].size() == 1)
                {
                    if(num)
                    {
                        if(b[u])
                        {
                            if(num != b[u])
                            {
                                cout << "NO\n";
                                return;
                            }
                        }
                        else b[u] = num;
                    }   
                    else
                    {
                        if(b[u]) num = b[u];
                    }
                }
            }

            b[i] = num;
            for(const int u : adj[i])
            {
                if(adj[u].size() == 1)
                {
                    b[u] = num;
                }
            }
        }
    }
    dfs(1,1);
    if(b[1] == 0)
    {
        b[1] = 1;
    }
    for(int i = 1;i<=n;i++)
    {
        if(b[i] == 0)
        {
            b[i] = b[fin(i)]; 
        }
    }
    if(ck())
    {
        cout << "YES\n";
        for(int i = 1;i<=n;i++) cout << b[i] << ' ';
        cout << '\n';
    }
    else cout << "NO\n";
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    
    while(t--)
    {
        solve();
    }
    return 0;
}