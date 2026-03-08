#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1983F.cpp Create time : 2026.03.04 22:21

struct trie
{
    struct Node{
        array<int, 2>next;
        int cnt;
        Node():next{}, cnt(){};
    };
    vector<Node>t;
    int root = 0;
    int cnt = 0;
    static constexpr int K = 29;

    trie():t(1){};

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    void insert(int x)
    {
        cnt++;
        int p = root;
        for(int i = K;i >= 0;i--){
            int v = (x >> i & 1);
            if(t[p].next[v] == 0)t[p].next[v] = newNode();
            p = t[p].next[v];
            t[p].cnt++;
        }
        return;
    }

    void del(int x)
    {
        cnt--;
        int p = root;
        for(int i = K;i >= 0;i--){
            int v = (x >> i & 1);
            if(t[p].next[v] == 0)t[p].next[v] = newNode();
            p = t[p].next[v];
            t[p].cnt--;
        }
        return;
    }

    int minxor(int x)
    {
        if(cnt == 0)return INT_MAX;
        int p = root;
        int ans = 0;
        for(int i = K;i >= 0;i--){
            int v = (x >> i & 1);
            if(t[p].next[v] == 0 || t[t[p].next[v]].cnt == 0){
                p = t[p].next[v ^ 1];
                ans += (1 << i);
            }
            else p = t[p].next[v];
        }
        return ans;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    i64 k;
    cin >> k;
    for(int i = 0;i < n; i++){
        cin >> a[i];
    }

    auto check = [&](int x) -> bool
    {
        i64 sum = 0;
        trie t;
        int p = 0;
        for(int i = 0;i < n;i++){
            while(t.minxor(a[i]) <= x){
                sum += n - i;
                t.del(a[p++]);
            }
            t.insert(a[i]);
        }
        if(sum >= k)return true;
        else return false;
    };

    i64 l = -1, r = 2e9;
    while(r - l > 1){
        i64 m = l + r >> 1;
        if(check(m)){
            r = m;
        }
        else{
            l = m;
        }
    }
    cout << r << endl;
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