#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.23 15:57:43
constexpr int M = 26;
struct trie{
    struct Node{
        int cnt;
        int exist;
        array<int, M>next;
        Node():cnt(0), exist(0),next{} {}
    };

    vector<Node>t;
    int ans = 0;
    int exc = 0;
    int m = 0;

    trie(){
        t.emplace_back();
    }

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    void insert1(string& s)
    {
        int p = 0;
        int n = s.length();
        for(int i = 0;i < n;i++){
            int x = s[i] - 'a';
            if(t[p].next[x] == 0){
                t[p].next[x] = newNode();
            }
            p = t[p].next[x];
            t[p].cnt++;
        }
        return;
    }

    void add(int p)
    {
        ans++;
        exc++;
        t[p].exist = 1;
    }

    void del(int p)
    {
        exc--;
        t[p].exist = 0;
    }

    void insert2(string& s)
    {
        int p = 0;
        int n = s.length();
        for(int i = 0;i < n;i++){
            int x = s[i] - 'a';
            p = t[p].next[x];
            if(!t[p].exist){
                add(p);
            }
            t[p].cnt--;
            if(t[p].cnt == 0 || exc > m){
                del(p);
            }
        }
        cerr << ans << endl;
    }

    void setM(int m_)
    {
        m = m_;
        return;
    }
};

// m = 1
// a a b b a b b , use 3


void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string>s(n);
    for(int i = 0;i < n;i++){
        cin >> s[i];
    }
    trie t;
    t.setM(m);
    for(int i = 0;i < n;i++){
        t.insert1(s[i]);
    }
    for(int i = 0;i < n;i++){
        t.insert2(s[i]);
    }
    int ans = t.ans;
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