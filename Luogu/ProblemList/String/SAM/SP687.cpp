#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct KMP
{
    string s;
    vector<int>fail;
    vector<int>slink;
    vector<int>diff;
    vector<vector<int>>ot;
    int suff;

    KMP(){init();}
    KMP(string& ss){init();for(auto ch :ss)add(ch);}

    void init()
    {
        suff = 0;
        s += '#';
        fail.assign(1, 0);
        slink.assign(1, -1);
        diff.assign(1, -1);
        ot.emplace_back();
    }
    

    void newNode()
    {
        fail.emplace_back();
        diff.emplace_back();
        slink.emplace_back();
        ot.emplace_back();
    }

    void add(char c)
    {
        s += c;
        newNode();
        int last = s.length() - 1;
        int cur = suff;
        while(cur != 0 && s[cur + 1] != s[last]){
            cur = fail[cur];
        }
        if(s[last] == s[cur + 1] && last != 1)fail[last] = cur + 1;
        else fail[last] = cur;
        diff[last] = last - fail[last];
        slink[last] = diff[last] == diff[fail[last]] ? slink[fail[last]] : fail[last];
        ot[fail[last]].push_back(last);
        suff = fail[last];
    }
    
};

void solve()
{
    int n;
    cin>>n;
    KMP kmp;
    auto&fail = kmp.fail;
    int ans = 0;
    for(int i = 1;i <= n;i++){
        char c;
        cin>>c;
        kmp.add(c);
        if()
    }
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