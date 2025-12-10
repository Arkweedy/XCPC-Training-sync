#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int lowbit(int x)
{
    return x & -x;
}

int cnt(int x)
{
    int res = 0;
    while(x != 0){
        x/=2;
        res++;
    }
    return res;
}

ll calc(int l, int r)
{
    int nl =  l / 3, nr = r / 3;
    int len = (nr - nl + 1) / 3;
    ll res = 3ll * len * (nl + nr) / 2;
    nl*=3,nr*=3;
    while(nl < l){
        res -= nl / 3;
        nl++;
    }
    while(nr < r){
        nr++;
        res += nr / 3;
    }   
    return res;
}

void solve()
{
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    vector<int>deg(n);
    for(int i = 0;i < n-1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    int m = n + 2;
    int a = lowbit(m), b;
    m -= a;
    if(m != a)b = m;
    else{a/=2;b = a;}
    a = cnt(a);
    b = cnt(b);
    vector<vector<int>>lev(max(a,b)+1);
    vector<int>scnt(n);
    vector<int>fa(n, -1);
    vector<int>vs(n);
    queue<int>q;
    vector<int>spc;

    auto vis = [&](int p, int s)->bool //vs s from p
    {
        if(fa[s] == p)return false;
        fa[p] = s;
        scnt[s]++;
        return;
    };

    auto ok =[&](int u, int v)->void
    {
        cout<<u+1<<" "<<v+1<<endl;
        return;
    };

    for(int i = 0;i < n;i++){
        if(deg[i] == 1){
            q.push(i);
            vs[i] = 2;
        }
        if(deg[i] == 4){
            spc.push_back(i);
        }
    }
    
    int all = (1 << a-1) + (1 << b - 1) - (a == 1) - (b == 1);

    if(a > b)swap(a,b);
    if(a == 1 && b == 1){
        cout<<1<<" "<<2<<endl;
        return;
    }
    else if(a == 1){
        //link to root:
        //link to middle:
        if(q.size() == all + 1){
            vector<int>faq;//father queue
            while(!q.empty()){
                int p = q.front();
                q.pop();
                for(auto s : g[p]){
                    if(vis(p,s)){
                        faq.push_back(s);
                    }
                }
            }
            for(auto p : faq){
                if(scnt[p] != 2){//1 or 3 ,but not care
                    for(auto s : g[p]){
                        if(fa[s] == p){
                            ok(s,p);
                            return;
                        }
                    }
                }
            }
        }else{//link to leaf:
            while(!q.empty()){
                int p = q.front();
                q.pop();
                if(deg[g[p][0]] == 2){
                    ok(p,g[p][0]);
                    return;
                }
            }
        }
    }
    else{// no tree that only one node
        if(q.size() == all){//no leaf linked
            vector<int>faq;//father queue
            while(!q.empty()){
                int p = q.front();
                q.pop();
                for(auto s : g[p]){
                    if(vis(p,s)){
                        faq.push_back(s);
                    }
                }
            }
        }
        else{//at least one leaf linked

        }
    }
    


    
    if(q.size() == all){
        int now = 1;
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : g[p]){
                if(vs[s] < 2){
                    vs[s]++;
                    fa[p] = s;
                    q.push(s);
                }
            }
        }
    }
    else{
        vector<int>faq;//father queue
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : g[p]){
                if(vs[s] < 2){
                    vs[s]++;
                    fa[p] = s;
                    faq.push_back(s);
                }
            }
        }
        //find father the deg != 2
        int key = -1;
        for(auto s : faq){
            if(deg[s] != 2){
                key = s;
                break;
            }
        }
        if(g[key].size() == 2){
            int ans = deg[g[key][0]] == 2 ? g[key][1] : g[key][0];
            cout<<ans+1<<" "<<key+1<<endl; 
        }else{
            //blank in fa'fa
            for(auto p : faq){
                for(auto s : g[p]){
                    if(vs[s] < 2){
                        vs[s]++;
                        fa[p] = s;
                        faq.push_back(s);
                    }
                }
            }

            int ans = -1;
            for(auto s : g[key]){
                if(vs[s])
            }
            
        }
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