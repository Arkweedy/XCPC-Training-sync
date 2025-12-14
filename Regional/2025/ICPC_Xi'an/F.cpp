#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;

void solve()
{
    int n;
    cin>>n;
    vector<int>to(n);
    vector<vector<int>>g(n);
    vector<vector<int>>rg(n);
    vector<int>indeg(n);
    for(int i = 0;i < n;i++){
        cin>>to[i];
        to[i]--;
        indeg[to[i]]++;
        g[i].push_back(to[i]);
        g[to[i]].push_back(i);
        rg[to[i]].push_back(i);
    }

    vector<int>a(n);
    for(int i =  0;i < n;i++){
        cin>>a[i];
        a[i] *= 2;
    }

    vector<int>dir(n);
    for(int i = 0;i < n;i++){
        if(a[i] < a[to[i]])dir[i] = 1;
        else dir[i] = -1;
    }


    vector<int>vs(n);
    vector<int>cir(n, 1);
    vector<int>ctree;
    vector<int>ans(n);
    vector<int>endpos(n);

    auto calc = [&](int p)->void
    {
        if(dir[p] == dir[to[p]]){
            ans[p] = abs(a[p] - a[to[p]]) + ans[to[p]];
        }
        else{
            int t = abs(a[p] - a[to[p]]) / 2;
            if(t <= ans[to[p]])ans[p] = t;
            else ans[p] = t * 2 - ans[to[p]];
        }
        return;
    };
    
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        if(vs[p])return;
        vs[p] = 1;
        ctree.push_back(p);
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
            }
        }
        return;
    };

    auto get = [&](auto&&self, int p ,int root)->void
    {
        if(p != root){
            calc(p);
        }
        for(auto s : rg[p]){
            if(s != root){
                self(self, s, root);
            }
        }

    };


    for(int i = 0;i < n;i++){
        if(!vs[i]){
            dfs(dfs, i, -1);
            //
            queue<int>q;
            for(auto p : ctree){
                if(indeg[p] == 0)q.push(p);
            }
            while(!q.empty()){
                int p = q.front();
                q.pop();
                cir[p] = false;
                indeg[to[p]]--;
                if(indeg[to[p]] == 0)q.push(to[p]);
            }
            
            int bg = -1;
            for(auto p : ctree){
                if(cir[p]){
                    //cerr<<dir[p] <<" "<<dir[to[p]]<<endl;
                    //check spc
                    if(dir[p] + dir[to[p]] == 0 && (a[p] - a[to[to[p]]]) * dir[p] >= 0){
                        bg = p;
                        break;
                    }
                }
            }
            assert(bg != -1);
            //cerr<<bg<<endl;
            ans[bg] = abs(a[bg] - a[to[bg]]) / 2;
            get(get, bg, bg);
            ctree.clear();
        }
    }

    for(int i = 0;i < n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}