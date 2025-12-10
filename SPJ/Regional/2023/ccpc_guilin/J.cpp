#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.20 14:08:21

class Euler_graph_dir
{
    int n;
    vector<vector<int>>g;
    vector<int>indeg,outdeg;
    vector<int>cur;
    pair<int,int>odd_deg;

    void Hierholzer(int p)
    {
        for(auto&i = cur[p];i < g[p].size();){
            int s = g[p][i];
            i++;
            Hierholzer(s);
        }
        ans.push_back(p);
    }

public:
    vector<int>ans;//stack

    Euler_graph_dir(int n_)
        :n(n_),odd_deg(-1,-1)
    {
        g.resize(n);
        indeg.resize(n);
        outdeg.resize(n);
        cur.resize(n);
    }

    void add_edge(int u,int v)
    {
        g[u].push_back(v);
        indeg[v]++;
        outdeg[u]++;
    }

    bool check_euler()
    {
        int ok = 1;
        for(int i = 0;i < n;i++){
            ok &= (indeg[i] == outdeg[i]);
        }
        return ok;
    }

    bool check_semi_euler()
    {
        int eq = 0,gre = 0,les = 0;
        for(int i = 0;i < n;i++){
            if(indeg[i] == outdeg[i]){
                eq++;
            }else if(indeg[i] + 1 == outdeg[i]){
                odd_deg.first = i;
                les++;
            }else if(indeg[i] == outdeg[i] + 1){
                odd_deg.second = i;
                gre++;
            }else{
                return false;
            }
        }
        return (eq == n - 2 && gre == 1 && les == 1) || (eq == n);
    }

    void get_euler_path()
    {
        if(!check_semi_euler())return;
        if(odd_deg.first != -1){
            Hierholzer(odd_deg.first);
        }
        else{
            for(int i = 0;i < n;i++){
                if(!g[i].empty()){
                    Hierholzer(i);
                    break;
                }
            }
        }
        reverse(ans.begin(),ans.end());
    }

    void get_euler_circuit()
    {
        if(!check_euler())return;
        for(int i = 0;i < n;i++){
            if(!g[i].empty()){
                Hierholzer(i);
                break;
            }
        }
        reverse(ans.begin(),ans.end());
    }

    void min_lexicographical()
    {
        for(auto& vec : g)
        {
            sort(vec.begin(),vec.end());
        }
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
    }

    
    vector<Euler_graph_dir> g(m, Euler_graph_dir(n * 8)); // i -> len(ap)
    vector<map<pair<int,int>, vector<int>>>mpps(m), mpsp(m); //apbs asbp
    constexpr int P1 = 1e9 + 7, P2 = 1e9 + 9;
    constexpr int B1 = 114514, B2 = 100;
    vector<int>b1(m),b2(m);
    b1[0] = b2[0] = 1;
    for(int i = 1;i < m;i++){
        b1[i] = 1ll * b1[i - 1] * B1 % P1;
        b2[i] = 1ll * b2[i - 1] * B2 % P2;
    }

    // a : idx i(n) * len j(m)
    // b : idx

    


    auto add = [&](string s,int id, int type)->void
    {
        vector<int>p1(m),p2(m),s1(m + 1),s2(m + 1);
        for(int i = 0;i < m;i++){
            if(i){
                p1[i] = 1ll * p1[i - 1] * B1 % P1;
                p2[i] = 1ll * p2[i - 1] * B2 % P2;
            }
            p1[i] = (p1[i] + s[i]) % P1;
            p2[i] = (p2[i] + s[i]) % P2;
        }
        for(int i = m - 1;i >= 0;i--){
            s1[i] = (s1[i + 1] + 1ll * s[i] * b1[m - i - 1]) % P1;
            s2[i] = (s1[i + 1] + 1ll * s[i] * b2[m - i - 1]) % P2;
        }

        // a[1... k] b[k + 1, ... m -1]
        if(type == 1){// a
            for(int i = 0;i < m;i++){
                auto p = make_pair(p1[i],p2[i]);
                auto s = make_pair(s1[m - i - 1], s2[m - i - 1]);
                mpps[i][p].push_back(id);
                mpsp[i][s].push_back(id + n);
            }
        }
        else if(type == 2){
            for(int i = 0;i < m;i++){
                //cerr<<id<<" "<<s1[i]<<" "<<s2[i]<<endl;
                auto p = make_pair(p1[m - i - 1],p2[m - i - 1]);
                auto s = make_pair(s1[i], s2[i]);
                mpps[m - i - 1][s].push_back(id + n * 3);
                mpsp[m - i - 1][p].push_back(id + n * 2);
            }
        }
    };

    for(int i = 0;i < n;i++){
        add(a[i], i, 1);
        add(b[i], i, 2);
    }

    // ap -> hs1 -> bs -> bp -> hs1 -> as -> ap

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            //as -> ap
            g[j].add_edge(i + n, i);
            //bp -> bs
            g[j].add_edge(i + n * 2, i + n * 3);
        }
    }

    for(auto [hs, vec] : mpps[0]){
        cerr<<hs.first<<","<<hs.second<<":"<<endl;
        for(auto x : vec){
            cerr<<x<<" ";
        }
        cerr<<endl;
    }
    


    for(int i = 0;i < m;i++){
        int tot = n * 4;
        for(auto [hs, vec] : mpps[i]){
            for(auto v : vec){// ap / bs
                if(v < n)g[i].add_edge(v, tot);
                else g[i].add_edge(tot, v);
            }
            tot++;
        }
        for(auto [hs, vec] : mpsp[i]){
            for(auto v : vec){// as / bp
                if(v < n * 2)g[i].add_edge(tot, v);
                else g[i].add_edge(v, tot);
            }
            tot++;
        }
    }

    for(int i = 0;i < m;i++){
        
        if(!g[i].check_euler()){
            cerr<<"no"<<endl;
            continue;
        }
        g[i].get_euler_circuit();
        cerr<<g[i].ans.size()<<endl;
        if(g[i].ans.size() == n * 6){
            //
            vector<int>ansa, ansb;
            for(auto x : g[i].ans){
                if(x < n)ansa.push_back(x);
                if(n * 2 <= x && x < n * 3)ansb.push_back(x - n * 2);
            }
            reverse(ansa.begin(),ansa.end());
            reverse(ansb.begin(),ansb.end());
            for(int i = 0;i < n;i++){
                cout << ansa[i] + 1 << " ";
            }
            cout<<endl;
            for(int i = 0;i < n;i++){
                cout << ansb[i] + 1 << " ";
            }
            cout<<endl;
            return;
        }
    }
    cout<<-1<<endl;
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