#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1625D.cpp Create time : 2026.02.21 00:08

// 找一个最大集S, \forall i, j \in S,  a_i ^ a_j \geq k
// |S| \geq 2
// S 是否合法只和 xor min 有关
// xor min 是哪个？

// 不能同时选的连边
// 图上的最大独立集？
// 显然边数可以很多，不太可行

// 有没有一些 xor 不等式可以用来推理性质的？

// if a < b < c , xor min is a ^ b / b ^ c
// 只有相邻的才可能是xor min
// 可以维护一个前缀trie实现边dp边插入

struct trie
{
    struct Node{
        array<int, 2>next;
        int ma;
        int id;
        Node():next{}, ma(), id(){};
    };
    vector<Node>t;
    int root = 0;
    static constexpr int K = 29;

    trie():t(1){};

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    void insert(int x, int cnt, int id)
    {
        int p = root;
        for(int i = K;i >= 0;i--){
            int v = (x >> i & 1);
            if(t[p].next[v] == 0)t[p].next[v] = newNode();
            p = t[p].next[v];
            if(cnt > t[p].ma){
                t[p].id = id;
                t[p].ma = max(t[p].ma, cnt);
            }
        }
        return;
    }

    pair<int,int> query(int x, int k)
    {
        int p = root;
        int res = 1;
        int pre = -1;
        for(int i = K;i >= 0;i--){
            int v = (k >> i & 1);
            int u = (x >> i & 1);
            if(v == 0){
                // walk 1, all ok
                if(t[p].next[u ^ 1]){
                    int s = t[p].next[u ^ 1];
                    if(res < t[s].ma + 1){
                        res = max(res,t[s].ma + 1);
                        pre = t[s].id;
                    }
                }
            }
            p = t[p].next[v ^ u];
            if(p == 0)break;
            // to it
            if(i == 0){
                int s = p;
                if(res < t[s].ma + 1){
                    res = max(res,t[s].ma + 1);
                    pre = t[s].id;
                }
            }
        }
        return {res, pre};
    }
    
};

// 构造方案 ： find pre

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>id(n);
    iota(id.begin(),id.end(), 0);
    sort(id.begin(),id.end(), [&](int i, int j)->bool
    {
        return a[i] < a[j];
    });
    trie t;
    int ans = 0;
    int ansp = -1;
    vector<int>pre(n);
    for(int i = 0;i < n;i++){
        int v = a[id[i]];
        auto [res, pr] = t.query(v, k);
        pre[id[i]] = pr;
        if(ans < res){
            ans = res;
            ansp = id[i];
        }
        t.insert(v, res, id[i]);
    }
    if(ans == 1){
        cout << -1 << endl;
    }
    else{
        cout << ans << endl;
        while(ansp != -1){
            cout << ansp + 1 << " ";
            ansp = pre[ansp];
        }
        cout << endl;
    }
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