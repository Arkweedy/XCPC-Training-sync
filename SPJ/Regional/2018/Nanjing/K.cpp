#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 1e5 + 10;

void sovle() 
{
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<array<vector<int>, 4>> g(n * m); // rg
    vector<array<vector<int>, 4>> tg(n * m); // rg
    auto ok = [&](int x, int y) -> bool {
        return x >= 0 && y >= 0 && x < n && y < m && a[x][y] == '1';
    };
    array<int, 4> dx = {1, 0, -1, 0}, dy = {0, -1, 0, 1}; // D
    auto add = [&](int u, int v, int k) -> void {
        tg[u][k].push_back(v);
        g[v][k].push_back(u);
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!ok(i, j)) continue;
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k], y = j + dy[k];
                if (ok(x, y)) {
                    add(i * m + j, x * m + y, k);
                } else {
                    add(i * m + j, i * m + j, k);
                }
            }
        }
    }
    int len = n * m;
    int N = n * m * n * m;
    vector<int> vs(N);
    vector<int> pre(N, -1);
    vector<int> op(N, -1);
    queue<int> q;
    for (int i = 0; i < n * m; i++) {
        int p = i * len + i;
        vs[p] = 1;
        pre[p] = -1;
        q.push(p);
    }
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        int u = p / len, v = p % len;
        for (int i = 0; i < 4; i++) {
            for (auto nu : g[u][i]) {
                for (auto nv : g[v][i]) {
                    int np = nu * len + nv;
                    if (!vs[np]) {
                        vs[np] = 1;
                        pre[np] = p;
                        op[np] = i;
                        q.push(np);
                    }
                }
            }
        }
    }
    vector<int> pos(len);
    iota(pos.begin(), pos.end(), 0);
    string ans;
    array<char, 4> dir = {'D', 'L', 'U', 'R'};
    auto move = [&](int op) -> void {
        for (int i = 0; i < len; i++) {
            if(ok(pos[i] / m, pos[i] % m)){
                pos[i] = tg[pos[i]][op][0];
            }
        }
        ans += dir[op];
    };
    auto merge = [&](int u, int v) -> void {
        int p = u * len + v;
        while (p % len != p / len) {
            move(op[p]);
            p = pre[p];
        }
        //cerr<<u<<" "<<v<<endl;
        return;
    };
    int bg = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '1') bg = i * m + j;
        }
    }
    for (int i = 0; i < N; i++) {
        //cerr << pre[i] << ' ' << op[i] << endl;
    }
    for (int i = 0; i < len; i++) {
        int x = i / m, y = i % m;
        if (a[x][y] == '1'){ 
            merge(pos[bg], pos[i]);
            assert(pos[bg] == pos[i]);
        }
    }
    cout << ans << endl;
    cerr << ans.size() << endl;
    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        sovle();
    }
    return 0;
}