#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int M = 400;

int a[N],n,q,id[N],B;
int tot;
ll ans[N],val[N];
vector<int>e[N];
vector<array<int,3>>que[N];
bool st[N];
void solve()
{
    cin>>n>>q;
    vector<int>b;
    set<int>s;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        s.insert(a[i]);
        b.push_back(a[i]);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    int m = b.size();
    for(int i=1;i<=n;i++){
        a[i] = lower_bound(b.begin(),b.end(),a[i]) - b.begin();
        e[a[i]].push_back(i);
    }
    B = sqrt(n);
    for(int i=0;i<m;i++)if(e[i].size() >= B)st[i] = 1;

    for(int i=1;i<=q;i++){
        int x,y;cin>>x>>y;
        //cout<<x<<' '<<y<<endl;
        if(!s.count(x) || !s.count(y)){
            continue;
        }
        x = lower_bound(b.begin(),b.end(),x)-b.begin();
        y = lower_bound(b.begin(),b.end(),y)-b.begin();

        if(x==y){
            ans[i] = 1ll * e[x].size() * (e[x].size()-1)/2;
            continue;
        }
        int id =i;
        if(!st[x] && !st[y]){
            int i = 0,j = 0;
            while(i<e[x].size()){
                while(j<e[y].size() && e[y][j] < e[x][i])j++;
                ans[id] += e[y].size() - j;
                i++;
            }
        }
        else if(st[y]){
            que[y].push_back({x,i,0});

        }
        else {
            que[x].push_back({y,i,1});
        }
    }


    for(int i=0;i<m;i++){
        if(st[i]){
            id[i] = ++tot;
            int sz = e[i].size(),k = 0;
            for(int j=0;j<m;j++)val[j] = 0;
            for(int j=1;j<=n;j++){
                while(k < sz && e[i][k] <= j){
                    k++;
                }
                if(a[j]!=i){
                    val[a[j]] += sz - k;
                }

            }
            for(auto [x,id,op]:que[i]){
                ans[id] = val[x];
                if(op)ans[id] = e[x].size() * e[i].size() - ans[id];
            }
        }
    }
    for(int i=1;i<=q;i++)cout<<ans[i]<<'\n';
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}
