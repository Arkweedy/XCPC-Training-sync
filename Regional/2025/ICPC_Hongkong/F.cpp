#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int op;
    cin >> op;
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v;
    }

    if (op == 1) {
        int k;
        cin >> k;
        vector<int> a(k+1);
        for (int i = 1; i <= k; i++) cin >> a[i];

        vector<int> pos(n+1, 0), rk(n+1, 0);
        for (int i = 1; i <= k; i++) pos[a[i]] = i, rk[a[i]] = i;

        int cur = k;
        for (int v = 1; v <= n; v++) {
            if (!pos[v]) rk[v] = ++cur;
        }

        // 判断环相邻：pos[u] -> pos[v] 是否是环方向相邻
        auto isNext = [&](int u, int v)->bool{
            if (!pos[u] || !pos[v]) return false;
            int pu = pos[u], pv = pos[v];
            return (pu % k) + 1 == pv;
        };

        for (int i = 0; i < m; i++) {
            int u = edges[i].u, v = edges[i].v;
            if (pos[u] && pos[v]) {
                if (isNext(u, v)) {
                    cout << u << " " << v << "\n";
                } else if (isNext(v, u)) {
                    cout << v << " " << u << "\n";
                } else {
                    if (pos[u] < pos[v]) cout << u << " " << v << "\n";
                    else cout << v << " " << u << "\n";
                }
            } else {
                if (rk[u] < rk[v]) cout << u << " " << v << "\n";
                else cout << v << " " << u << "\n";
            }
        }
        return 0;
    }

    // op == 2
    // Build adjacency (directed) and reverse adjacency for SCC
    vector<int> head(n+1, -1), headR(n+1, -1), to(m), nxt(m), toR(m), nxtR(m);
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        to[i] = v; nxt[i] = head[u]; head[u] = i;
        toR[i] = u; nxtR[i] = headR[v]; headR[v] = i;
    }

    // Kosaraju first pass: order
    vector<char> vis(n+1, 0);
    vector<int> order;
    order.reserve(n);

    for (int s = 1; s <= n; s++) if (!vis[s]) {
        vector<int> st;
        vector<int> it;
        st.push_back(s);
        it.push_back(head[s]);
        vis[s] = 1;

        while (!st.empty()) {
            int u = st.back();
            int &eid = it.back();
            if (eid == -1) {
                st.pop_back();
                it.pop_back();
                order.push_back(u);
            } else {
                int e = eid;
                eid = nxt[e];
                int v = to[e];
                if (!vis[v]) {
                    vis[v] = 1;
                    st.push_back(v);
                    it.push_back(head[v]);
                }
            }
        }
    }

    // second pass: assign components
    vector<int> comp(n+1, -1);
    vector<int> compsize;
    int cid = 0;
    for (int idx = (int)order.size()-1; idx >= 0; idx--) {
        int s = order[idx];
        if (comp[s] != -1) continue;
        compsize.push_back(0);
        vector<int> st;
        st.push_back(s);
        comp[s] = cid;

        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            compsize[cid]++;
            for (int e = headR[u]; e != -1; e = nxtR[e]) {
                int v = toR[e];
                if (comp[v] == -1) {
                    comp[v] = cid;
                    st.push_back(v);
                }
            }
        }
        cid++;
    }

    // find SCC with size > 1 (cycle SCC)
    int cycComp = -1;
    for (int i = 0; i < cid; i++) {
        if (compsize[i] > 1) {
            if (cycComp == -1 || compsize[i] > compsize[cycComp]) cycComp = i;
        }
    }

    // collect vertices in SCC
    vector<int> inC(n+1, 0), verts;
    for (int v = 1; v <= n; v++) {
        if (comp[v] == cycComp) {
            inC[v] = 1;
            verts.push_back(v);
        }
    }
    int K = (int)verts.size();

    // build edges inside SCC (local indexing)
    vector<int> sU, sV;
    vector<int> headS(n+1, -1), nxtS, toS;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        if (inC[u] && inC[v]) {
            int id = (int)sU.size();
            sU.push_back(u);
            sV.push_back(v);
            toS.push_back(v);
            nxtS.push_back(headS[u]);
            headS[u] = id;
        }
    }
    int ES = (int)sU.size();

    // find any directed cycle inside SCC using DFS colors
    vector<char> color(n+1, 0);
    vector<int> parentV(n+1, -1), parentE(n+1, -1);
    vector<int> cycleEdges;

    for (int start : verts) {
        if (color[start]) continue;
        vector<int> st, it;
        st.push_back(start);
        it.push_back(headS[start]);
        color[start] = 1;

        while (!st.empty() && cycleEdges.empty()) {
            int u = st.back();
            int &eid = it.back();
            if (eid == -1) {
                color[u] = 2;
                st.pop_back();
                it.pop_back();
                continue;
            }
            int e = eid;
            eid = nxtS[e];
            int v = toS[e];

            if (color[v] == 0) {
                color[v] = 1;
                parentV[v] = u;
                parentE[v] = e;
                st.push_back(v);
                it.push_back(headS[v]);
            } else if (color[v] == 1) {
                // found back edge u -> v
                vector<int> path;
                int cur = u;
                path.push_back(cur);
                while (cur != v) {
                    cur = parentV[cur];
                    path.push_back(cur);
                }
                reverse(path.begin(), path.end()); // v ... u

                // edges along path
                for (int i = 1; i < (int)path.size(); i++) {
                    cycleEdges.push_back(parentE[path[i]]);
                }
                cycleEdges.push_back(e); // closing edge
                break;
            }
        }
        if (!cycleEdges.empty()) break;
    }

    // check function: remove subset edges -> SCC acyclic?
    vector<int> mark(ES, 0);
    int tag = 1;

    auto check = [&](const vector<int>& removed)->bool{
        tag++;
        for (int e : removed) mark[e] = tag;

        vector<int> indeg(n+1, 0);
        for (int e = 0; e < ES; e++) {
            if (mark[e] == tag) continue;
            indeg[sV[e]]++;
        }
        deque<int> q;
        for (int v : verts) if (indeg[v] == 0) q.push_back(v);

        int cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop_front();
            cnt++;
            for (int e = headS[u]; e != -1; e = nxtS[e]) {
                if (mark[e] == tag) continue;
                int v = toS[e];
                if (--indeg[v] == 0) q.push_back(v);
            }
        }
        return cnt == K;
    };

    // binary search edge that breaks all cycles
    vector<int> P = cycleEdges;
    while ((int)P.size() > 1) {
        int mid = (int)P.size() / 2;
        vector<int> A(P.begin(), P.begin() + mid);
        vector<int> B(P.begin() + mid, P.end());
        if (check(A)) P = A;
        else P = B;
    }
    int cutEdge = P[0];

    // topo sort SCC after removing cutEdge
    tag++;
    mark[cutEdge] = tag;

    vector<int> indeg(n+1, 0);
    for (int e = 0; e < ES; e++) {
        if (mark[e] == tag) continue;
        indeg[sV[e]]++;
    }
    deque<int> q;
    for (int v : verts) if (indeg[v] == 0) q.push_back(v);

    vector<int> ans;
    ans.reserve(K);
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        ans.push_back(u);
        for (int e = headS[u]; e != -1; e = nxtS[e]) {
            if (mark[e] == tag) continue;
            int v = toS[e];
            if (--indeg[v] == 0) q.push_back(v);
        }
    }

    // output cycle vertices in cyclic order (topo gives a valid rotation)
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
