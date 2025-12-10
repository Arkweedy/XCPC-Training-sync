#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

vector<int> prefix_function(const string& s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}



struct trie{
    struct Node
    {
        array<int,3>next;
        int cnt;
        int len;
        int maxlen;
        Node():next{},cnt{},len{},maxlen{}{};
    };
    vector<Node>t;

    trie()
    {
        t.assign(2,Node());
        t[0].next.fill(1);
        t[0].cnt = 0;
        t[0].len = 0;
        t[0].maxlen = 0;
    }

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    int num(char c)
    {
        return c - 'a';
    }

    void add(const string&s, int weight)
    {
        int p = 1;
        int len = s.length();
        int maxlen = 0;
        string x;
        for(int i = 0;i < len * 2 || i < t[p].maxlen;i++){
            if(next(p,s[i%len]) == 0){
                next(p,s[i%len]) = newNode();
                t[next(p,s[i%len])].len = t[p].len + 1; 
            }
            x += s[i % len];
            p = next(p,s[i%len]);
            t[p].cnt+=weight;
            maxlen++;
        }
        p = 1;
        for(int i = 0;i < maxlen;i++){
            p = next(p,s[i%len]);
            t[p].maxlen = max(t[p].maxlen,maxlen);
        }
        
        return;
    }

    int& next(int p, char c)
    {
        return t[p].next[num(c)];
    }

};

void solve()
{
    int n;
    cin>>n;
    vector<string>s(n);
    for(int i = 0;i < n;i++){
        cin>>s[i];
        replace(s[i].begin(),s[i].end(),'P','a');
        replace(s[i].begin(),s[i].end(),'N','b');
        replace(s[i].begin(),s[i].end(),'K','c');
    }
    vector<vector<int>>pi(n);
    vector<string>mins(n);
    trie ti;
    
    for(int i = 0;i < n;i++){
        int len = s[i].length();
        pi[i] = prefix_function(s[i]);
        int p = len - 1;
        mins[i] = s[i];
        if(len % (len - pi[i][p]) == 0){
            mins[i] = s[i].substr(0,len - pi[i][p]);
        }
        else{
            mins[i] = s[i];
        }
        //cerr<<mins[i]<<endl;
    }
    map<string,int>mp;
    for(int i = 0;i < n;i++){
        mp[mins[i]]++;
    }
    vector<pair<string,int>>a;
    for(auto pr : mp){
        a.push_back(pr);
    }

    int m = a.size();
    vector<int>id(m);
    iota(id.begin(),id.end(),0);
    sort(id.begin(),id.end(),[&](int i, int j)->bool
    {
        return a[i].first.length() > a[j].first.length();
    });

    for(int i = 0;i < m;i++){
        ti.add(a[id[i]].first,a[id[i]].second);
    }

    const auto& t = ti.t;
    int tot = t.size();
    ll ans = 0;
    for(int i = 1;i < tot;i++){
        ans += 1ll * t[t[i].next[0]].cnt * t[t[i].next[1]].cnt * t[t[i].next[2]].cnt;
    }
    cout<<ans<<endl;
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