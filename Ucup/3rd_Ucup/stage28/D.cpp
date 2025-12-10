#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct SAM{
    static constexpr int M = 26;
    struct Node
    {
        int len;
        int link;
        array<int,M>next;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;

    int last = 1;
    
    SAM(){init();}
    SAM(string&s){init();build(s);}

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[0].next.fill(1);
    }

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    static int num(int x)
    {
        return x - 'a';
    }

    void extend(int x)
    {
        int cur - newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while(p != 0 && t[p].next[x] == 0){
            t[p].next[x] = cur;
            p = t[p].link;
        }
        int q = t[p].next[x];
        if(p == 0){
            t[cur].link = 1;
        }
        else if(t[q].len == t[p].len + 1){
            t[cur].link = q;
        }
        else{
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone]
        }
    }
    
}

void solve()
{
    
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