#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 2e5 + 10;

int f[N];

int find(int x){
    if(f[x]!=x)f[x] = find(f[x]);
    return f[x];
}

void merge(int u,int v){
    u = find(u), v = find(v);
    if(u==v)return;
    if(u<v)swap(u,v);
    f[v] = u;
}

void solve()
{
    int n,m;cin>>n>>m;
    int temp = m;
    set<int>s;
    vector<vector<int>>e(n+1);
    while(m--){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
        s.insert(u);
        s.insert(v);
    }
    
    if(n==2){
        cout<<"YES\n";
        cout<<"1 2\n";
        return;
    }
    
    if(s.size() == n){
        cout<<"NO\n";
        return;
    }
    
    if(s.size() == n-1){
        if(temp == 1ll * (n-1)*(n-2)/2){
            cout<<"YES\n";
            int t = 1;
            while(s.count(t))t++;
            for(int i=1;i<=n;i++){
                if(i==t)continue;
                cout<<i<<' '<<t<<'\n';
            }
        }
        else{
            cout<<"NO\n";
        }
        return;
    }
    
    vector<int>id,p(n+1);
    for(auto u:s)id.push_back(u),p[u] = id.size() - 1;
    
    int k = id.size();
    for(int i=0;i<k;i++)f[i] = i;
    vector<int>st(k);
    for(int i=1;i<=n;i++){
        if(e[i].empty())continue;
        int u = p[i];
        sort(e[i].begin(),e[i].end());
        int pre = -1;
        for(auto j:e[i]){
            int v = p[j];
            int l = pre + 1,r = v - 1;
            if(l<=r){
                merge(u,l);
                st[l]++,st[r]--;
            }
            pre = v;
        }
        int l = pre + 1,r = k - 1;
        if(l<=r){
            merge(u,l);
            st[l]++,st[r]--;
        }
    }
    
    for(int i=1;i<k;i++)st[i] += st[i-1];
    for(int i=0;i<k;i++)if(st[i])merge(i,i+1);

    set<int>cnt;
    vector<int>c;
    
    map<int,int>g;
    
    for(int i=0;i<k;i++)cnt.insert(find(i));
    
    for(int i=1;i<=n;i++){
        for(auto j:e[i]){
            if(find(p[i]) == find(p[j])){
                cout<<"NO\n";
                return;
            }
        }
    }
    
    if(cnt.size()==2){
        cout<<"YES\n";
        vector<int> ve;
        for(int i=1;i<=n;i++)
        {
            if(s.count(i)) continue;
            ve.push_back(i);
        }
        int m=(int)ve.size()-1;
        for(int i=0;i<m;i++)
        {
            cout<<ve[i]<<' '<<ve[i+1]<<'\n';
        }
        int l = k+1,r = -1;
        for(int i=0;i<k;i++)l = min(l,find(i)),r = min(r,find(i));
        
        for(int i=0;i<k;i++){
            if(find(i)==l)cout<<id[i]<<' '<<ve[0]<<'\n';
            else cout<<id[i]<<' '<<ve.back()<<'\n';
        }
    }
    else{
        if(cnt.size() + 1 > n-k){
            cout<<"NO\n";
        }
        else{
            cout<<"YES\n";
            vector<int> ve;
            for(int i=1;i<=n;i++)
            {
                if(s.count(i)) continue;
                ve.push_back(i);
            }
            for(int i=1;i<ve.size();i++){
                cout<<ve[i]<<' '<<ve[0]<<'\n';
            }
            map<int,int>ha;
            for(int i=0;i<k;i++){
                int u = find(i);
                if(!ha.count(u)){
                    ha[u] = ve.back();
                    ve.pop_back();
                }
                cout<<id[i]<<' '<<ha[u]<<'\n';
            }
            
        }
        
        
    }


}


int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
