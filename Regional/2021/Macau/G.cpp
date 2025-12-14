#include<bits/stdc++.h>

#define ln (p<<1)
#define rn (p<<1|1)
using ll = long long;
using namespace std;

constexpr int N = 1e6 + 10,M = 2e6 + 10;

vector<pair<int,int>>e[M];
ll dp[M];
int cnt[N<<2],n,k,a[N],p[N];

void modify(int p,int l,int r,int x,int t){
    if(l==r){
        cnt[p] = t;
        return;
    }
    int mid = l+r>>1;
    if(x>mid)modify(rn,mid+1,r,x,t);
    else modify(ln,l,mid,x,t);
    cnt[p] = cnt[ln] + cnt[rn];
}

int query(int p,int l,int r,int k){
    if(r < k)return -1;
    if(l >= k){
        if(cnt[p] == r - l + 1)return -1;
        if(l==r)return l;
    }
    int mid = l+r>>1;
    int res = query(ln,l,mid,k);
    if(res != -1)return res;
    return query(rn,mid+1,r,k);
}

int dis(int a,int b){
    return min(abs(a-b),n-abs(a-b));
}

void solve()
{
    cin>>n>>k;
    for(int i=0;i<=2*n;i++){
        e[i].clear();
        dp[i] = 1e18;
    }

    for(int i=0;i<n;i++){
        cin>>a[i];a[i]--;
        p[a[i]] = i;
    }

    for(int i=0;i<n;i++)modify(1,0,n-1,i,0);
    for(int i=n-k;i<n;i++)modify(1,0,n-1,a[i],1);

    int T = 2*n;

    for(int i=0;i<n;i++){
        int x = (i-k+n)%n;
        modify(1,0,n-1,a[x],0);
        modify(1,0,n-1,a[i],1);
        int res = query(1,0,n-1,a[i]+1);
        if(res != -1){
            x = p[res];
            e[2 * a[i] + 1].push_back({2*res , dis(i,x+k-1)});
            e[2 * a[i] + 1].push_back({2*res+1 , dis(i,x)}); 
        }else{
            e[2*a[i] + 1].push_back({T,0});
        }
    }

    for(int i=0;i<n;i++)modify(1,0,n-1,i,0);
    for(int i=0;i<k;i++)modify(1,0,n-1,a[i],1);

    for(int i=n-1;i>=0;i--){
        int x = (i+k)%n;
        modify(1,0,n-1,a[x],0);
        modify(1,0,n-1,a[i],1);
        int res = query(1,0,n-1,a[i]+1);
        if(res!=-1){
            x = p[res];
            e[2*a[i]].push_back({2*res,dis(i,x)});
            e[2*a[i]].push_back({2*res+1,dis(i,x-k+1)});
        }else{
            e[2*a[i]].push_back({T,0});
        }
    }

    int S = query(1,0,n-1,0);

    if(S == -1){
        cout<< 0 <<'\n';
        return;
    }

    priority_queue<pair<ll,int>>heap;

    dp[2*S] = dis(0,p[S]);
    dp[2*S+1] = dis(0,p[S]-k+1);
    heap.push({-dp[2*S],2*S});
    heap.push({-dp[2*S+1],2*S+1});

    vector<int>vis(2*n+1);
    while(!heap.empty()){
        auto [_,u] = heap.top();
        heap.pop();
        if(vis[u])continue;
        vis[u] = 1;
        for(auto [v,w]:e[u]){
            if(dp[v] > dp[u] + w){
                dp[v] = dp[u] + w;
                heap.push({-dp[v],v});
            }
        }
    }

    cout<<dp[T]<<'\n';

    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}