#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.04.10 09:49:28

constexpr int M = 26;
struct trie{
    struct Node{
        array<int, M>next{};
        int cnt = 0;
        int end = 0;
    };

    vector<Node>t;

    trie():t(1){};

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    void insert(string s)
    {
        int p = 0;
        t[p].cnt++;
        for(int i = 0;i < s.length();i++){
            int x = s[i] - 'a';
            if(t[p].next[x] == 0){
                t[p].next[x] = newNode();
            }
            p = t[p].next[x];
            t[p].cnt++;
        }
        t[p].end++;
        return;
    }

    void query(int p, int k, string&ans)
    {
        for(int i = M - 1;i >= 0;i--){
            if(t[p].next[i] != 0){
                if(k >= t[t[p].next[i]].cnt - 1){
                    k -= t[t[p].next[i]].cnt - 1;
                }
                else{
                    ans += 'a' + i;
                    query(t[p].next[i], k, ans);
                    break;
                }
            }
        }
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    trie t;
    for(int i = 0; i < n;i++){
        string s;
        cin >> s;
        t.insert(s);
    }
    k = n - k;
    string ans;
    t.query(0, k, ans);
    if(ans.empty()){
        ans = "EMPTY";
    }
    cout << ans << endl;
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