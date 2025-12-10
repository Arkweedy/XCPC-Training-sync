#include<bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using i64 = long long;
using uint = unsigned int;

using namespace std;


void solve()
{
    int n, m, l;
    cin >> n >> m >> l;
    vector<int>a(l);
    for (int i = 0; i < l; i++) {
        cin >> a[i];
    }
    vector<vector<int>>g(n * 2);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v + n);
        g[v + n].push_back(u);
        g[v].push_back(u + n);
        g[u + n].push_back(v);
    }

    //bfs
    constexpr ll inf = 1145141919810;
    vector<ll>dis(n * 2, inf);
    vector<int>vs(n * 2);
    queue<int>q;
    q.push(0);
    dis[0] = 0;
    vs[0] = true;
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        for (auto s : g[p]) {
            if (!vs[s]) {
                vs[s] = true;
                q.push(s);
                dis[s] = dis[p] + 1;
            }
        }
    }

    ll sum = 0;
    sort(a.begin(), a.end());
    vector<int>odd, even;
    for (auto x : a) {
        sum += x;
        if (x % 2 == 0) {
            even.push_back(x);
        }
        else {
            odd.push_back(x);
        }
    }

    ll osum, esum;
    if (sum % 2 == 0) {
        esum = sum;
        if (!odd.empty()) {
            osum = sum - odd[0];
        }
        else {
            osum = 0;
        }
    }
    else {
        osum = sum;
        esum = sum - odd[0];
    }

    vector<int>ans(n);
    for (int i = 0; i < n; i++) {
        if (dis[i] <= esum) {
            ans[i] = 1;
        }
        if (dis[i + n] <= osum) {
            ans[i] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i];
    }
    cout << endl;
    return;
    
    
    

}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--)
        solve();
    return 0;
}