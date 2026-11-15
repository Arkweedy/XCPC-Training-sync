#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;
const int N = 2e5 + 9;
int fa[N * 2];
int b[N];
int fin[N* 2];
int cur;

int n,m;

vector<int> adj[N];
bool mark[N];

int ans1[N];
vector<pair<int,int>> ans2;
void dfs1(int i)
{
    mark[i] = true;
    ans1[i] = ++cur;
    for(const int son : adj[i])
    {
        if(mark[son]) continue;
        dfs1(son);
    }    
    ++cur;
}

void solve1()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i++)
    {
        mark[i] = false;   
        adj[i].clear();
    }
    cur = 0;
    for(int i = 1;i <= m;i++)
    {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1;i <= n;i++)
    {
        if(!mark[i])
        {
            dfs1(i);
        }
    }
    for(int i = 1;i <= n;i++)
    {
        cout << ans1[i] << ' ';
    }
    cout << '\n';
}
void solve2()
{
    cin >> n;
    ans2.clear();
    for(int i = 0;i <= n * 2;i++)
    {
        fa[i] = 0,fin[i] = 0;
    }
    for(int i = 1;i <= n;i++)
    {
        cin >> b[i];
        fin[b[i]] = i;
    }
    cur = 0;
    for(int i = 1;i <= n * 2;i++)
    {
        if(fin[i])
        {
            if(cur)
            {
                ans2.push_back({fin[i],fin[cur]});
                fa[i] = cur;
                cur = i;
            }
            else cur = i;
        }
        else cur = fa[cur];
    }
    cout << ans2.size() << '\n';
    for(const auto [x,y] : ans2) cout << x << ' ' << y << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string m;
    cin >> m;
    int tt = 1;
    cin >> tt;
    while(tt--)
    {
        if(m == "cat")solve1();
        else solve2();
    }
    return 0;
}