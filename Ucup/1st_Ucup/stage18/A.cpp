#include<bits/stdc++.h>
#include<bits/extc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
using Heap = __gnu_pbds::priority_queue<
    i64,
    std::less<i64>,
    __gnu_pbds::pairing_heap_tag
>;

//Create time: 2026.06.17 21:19:30

void solve()
{
    int n;
    cin >> n;
    i64 sum = 0;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i];
    }
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int>fa(n, -1);
    vector<Heap>heap(n);
    vector<i64>even(n);
    [&](this auto&&dfs, int p)->void
    {
        //cerr << p << endl;
        for(auto s : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                dfs(s);
                even[p] += even[s];
                heap[p].join(heap[s]);
            }
        }
        i64 cur = a[p];
        while(heap[p].size() >= 2 && heap[p].top() > cur){
            i64 x = heap[p].top();
            heap[p].pop();
            i64 y = heap[p].top();
            heap[p].pop();
            cur = cur - x + y;
        }
        if(heap[p].empty() || heap[p].top() <= cur){
            heap[p].push(cur);
        }
        else{
            even[p] += heap[p].top() - cur;
            heap[p].pop();
            assert(heap[p].empty());
        }
        return;
    }(0);

    i64 ans = 0;//X - Y
    i64 sign = 1;
    while(!heap[0].empty()){
        ans += sign * heap[0].top();
        sign = -sign;
        heap[0].pop();
    }
    ans -= even[0] * sign;
    ans = (ans + sum) / 2;
    cout << ans << endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}