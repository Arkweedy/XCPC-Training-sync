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
    ll w;
    cin>>n>>w;
    string s;
    cin>>s;
    KMP kmp(s);
    auto&fail = kmp.fail;
    auto&diff = kmp.diff;
    auto&slink = kmp.slink;
    constexpr ll inf = LLONG_MAX / 2;
    vector<ll>dis(n, inf);//mod n
    dis[0] = 0;
    int p = fail[n];

    auto tran_mod = [&](vector<ll>&mdis, int nmod)->vector<ll>
    {
        vector<ll>ndis(nmod, inf);
        int omod = mdis.size();
        int g = gcd(omod, nmod);
        for(int i = 0;i < omod;i++){
            ndis[mdis[i] % nmod] = min(ndis[mdis[i] % nmod], mdis[i]);
        }
        for(int i = 0;i < g;i++){
            int minpos = -1;
            ll mindis =  inf;
            for(int j = 0;j < nmod / g;j++){
                if(mindis > ndis[(i + 1ll * omod * j) % nmod]){
                    minpos = (i + 1ll * omod * j) % nmod;
                    mindis = ndis[minpos];
                }
            }
            if(mindis == inf)continue;
            for(int j = 1;j < nmod / g;j++){
                int pos = (minpos + 1ll * j * omod) % nmod;
                ndis[pos] = min(ndis[pos], mindis + 1ll * j * omod);
                mindis = min(mindis, ndis[pos] - 1ll * j * omod);
            }
        }
        return ndis;
    };

    while(p != 0){
        //calc p->slink[p]
        //x + kd
        //trans : dis[a + x + kd  mod x] <- dis[a  mod x] + x + kd  
        int d = diff[p];
        int x = n - p;
        int l = (p - slink[p]) / diff[p];
        int g = gcd(d, x);
        dis = tran_mod(dis, x);
        //cerr<<"trans : "<<d<<" "<<x<<" "<<l<<" "<<g<<endl;
        for(int i = 0;i < g;i++){
            deque<pair<ll,int>>dq;
            int minpos = -1;
            ll mindis = LLONG_MAX;
            for(int j = 0;j < x / g;j++){
                if(mindis > dis[(i + 1ll * d * j) % x]){
                    minpos = (i + 1ll * d * j) % x;
                    mindis = dis[minpos];
                }
            }
            if(mindis == inf)continue;
            dq.emplace_back(mindis, 0);
            for(int j = 1;j < x / g;j++){
                int pos = (minpos + 1ll * j * d) % x;
                if(j - dq.front().second >= l)dq.pop_front();
                if(!dq.empty())dis[pos] = min(dis[pos], dq.front().first + x + 1ll * j * d);
                while(!dq.empty() && dq.back().first > dis[pos] - 1ll * j * d)dq.pop_back();
                dq.emplace_back(dis[pos] - 1ll * j * d, j);
            }
        }
        p = slink[p];
    }

    ll ans = 0;
    dis = tran_mod(dis, n);
    for(int i = 0;i < n;i++){
        ans += max(0ll, w - dis[i]) / n;
    }
    cout<<ans<<endl;
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