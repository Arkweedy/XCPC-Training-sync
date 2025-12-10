#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

struct edge{
    int u,v,w;
    bool operator < (const edge & a)const{
        return w < a.w;
    }
};

int t[N],n,k,f[N];

int find(int x){
    if(f[x]!=x)f[x] = find(f[x]);
    return f[x];
}

void merge(int u,int v){
    u = find(u), v = find(v);
    if(u==v)return;
    f[v] = u;
}

int val(int a,int b){
    return (a+b)%k;
}

void solve()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>t[i],t[i]%=k,f[i] = i;
    sort(t+1,t+n+1);
    
    
    vector<edge>e;
    for(int i=1;i<=n;i++){
        
        for(int j=0;j<30;j++){
            if(1+j<=n)e.push_back({1+j,i,val(t[1+j],t[i])});
            if(n-j>0)e.push_back({i,n-j,val(t[i],t[n-j])});
        }

        e.push_back({n,i,val(t[n],t[i])});
        int l = 1,r = n + 1;
        while(l<r){
            int mid = l+r>>1;
            if(t[mid] + t[i] >= k)r = mid;
            else l=mid+1;
        }
        for(int j=0;j<30;j++){
            if(j+l<=n)e.push_back({i,j+l,val(t[i],t[j+l])});
        }
        e.push_back({i,l,val(t[i],t[l])});
    }
    
    sort(e.begin(),e.end());
    
    ll res  = 0;
    for(auto [u,v,w]:e){
        if(find(u) == find(v)){
            continue;
        }
        merge(u,v);
        res += w;
        //cout<<u<<' '<<v<<' '<<w<<endl;
        
    }
    cout<<res<<'\n';
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
