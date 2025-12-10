#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class segtree{
    int n;
    vector<ll>tree;

    void push_up(int p)
    {
        tree[p] = min(tree[p * 2], tree[p * 2 + 1]);
    }

    void update(int pos, ll val, int l,int r, int p)
    {
        if(l == r){
            tree[pos] = val;
        }
        else{
            int m = l + r >> 1;
            if(pos <= m)update(pos, val,l, m, p * 2);
            else update(pos,val,m+1,r,p*2+1);
            push_up(p);
        }
        return;
    }

public:
    segtree(int _n)
    {
        n = _n;
        tree.resize(n * 4);
    }

    void update(int pos, ll val)
    {
        update(pos,val,0,n-1,1);
    }

    ll qry()
    {
        return tree[1];
    }
}

void solve()
{
    int n, k;
    cin>>n>>k;
    vector<int>a(n),to(n);
    vector<vector<int>>g(n);
    vector<int>indeg(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>to[i];
        to[i]--;
        indeg[to[i]]++;
        g[i].push_back(to[i]);
        g[to[i]].push_back(i);
    }

    vector<int>vs(n);
    vector<int>id(n);
    for(int i = 0;i < n;i++){
        if(!vs[i]){
            //find circle
            vector<int>cir;
            vector<int>zr_indeg;
            vector<int>clr;
            int tot = 0;
            auto dfs = [&](auto&&self, int p, int fa)->void
            {
                if(vs[p]){
                    int x = p;
                    do{
                        cir.push_back(id[p]);
                        p = to[p];
                    }while(x != p);
                }
                else{
                    vs[p] = true;
                    id[p] = tot++;
                    clr.push_back(a[p]);
                    if(indeg[p] == 0)zr_indeg.push_back(p);
                    for(auto s : g[p]){
                        if(s != fa[p]){
                            self(self, s, p);
                        }
                    }
                }
                return;
            }
            dfs(dfs,0,-1);
            int m = cir.size();

            // pre process
            //find next same color 
            vector<int>nxt(tot, -1),steps(tot, -1);// id 
            for(auto p : zr_indeg){

            }

            //
            int len = ceil(log2(1e9));
            vector<vector<ll>>st(tot,vector<ll>(len));
            vector<vector<int>>nst(tot,vector<ll>(len));
            for(int i = 0;i < tot;i++){
                st[i][0] = step[i];
                nst[i][0] = nxt[i];
            }
            for(int j = 1;j < len;j++){
                for(int i = 0;i < n;i++){
                    st[i][j] = st[i][j - 1] + st[nst[i][j - 1]][j - 1];
                    nst[i][j] = nst[nst[i][j - 1]][j - 1];
                }
            }

            segtree<>


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