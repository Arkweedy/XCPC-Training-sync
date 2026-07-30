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
        int cur;
        array<int, M>next;
        Node():cur(0), next{} {}
    };

    vector<Node>t;
    vector<vector<int>>tid;
    set<int>st;
    int tot = 0;
    int ans = 0;
    int m = 0;

    trie(){
        t.emplace_back();
        tid.emplace_back();
    }

    int newNode()
    {
        tid.emplace_back();
        t.emplace_back();
        return t.size() - 1;
    }

    void vis(int p)
    {
        tid[p].push_back(tot++);
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
            vis(p);
        }
        return;
    }

    void vis2(int p)
    {
        int id = tid[p][t[p].cur];
        t[p].cur++;
        if(st.count(id)){
            st.erase(id);
            if(t[p].cur < tid[p].size()){
                st.insert(tid[p][t[p].cur]);
            }
        }
        else{
            ans++;
            if(t[p].cur < tid[p].size()){
                int nid = tid[p][t[p].cur];
                if(st.size() < m){
                    st.insert(nid);
                }
                else if(*(prev(st.end())) > nid){
                    st.erase(prev(st.end()));
                    st.insert(nid);
                }
            }
        }
    }

    void insert2(string& s)
    {
        int p = 0;
        int n = s.length();
        for(int i = 0;i < n;i++){
            int x = s[i] - 'a';
            p = t[p].next[x];
            vis2(p);
        }
    }

    void setM(int m_)
    {
        m = m_;
        return;
    }
};

// m = 1
// a a b b a b b , use 3
// a b a c c c c c b b b


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