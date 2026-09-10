#include <bits/stdc++.h>
#define N 2000009
using ll = long long;
using i64 = long long;
using namespace std;
int sa[N],sb[N],sc[N],sab[N],sac[N],dp[N],n;
struct node{
    int id,sab,sac;
};
int lowbit(int p){return p&(-p);}
bool cmp2( node aa,node bb){
    int a=aa.id,b=bb.id;
    if(sab[a]!=sab[b]) return sab[a]<sab[b];
    return a<b;
}
bool cmp1( node aa,node bb){
    int a=aa.id,b=bb.id;
    if(sac[a]!=sac[b]) return sac[a]<sac[b];
    return a<b;
}
struct bit{
    vector<int> tr;
void add(int p,int b){
    while(p<tr.size()){tr[p]=max(tr[p],b),p+=lowbit(p);}
}
int query(int p){
    int ans=-1e9;
    while(p){
    ans=max(ans,tr[p]);p-=lowbit(p);}
    return ans;
}
};
bit ab[N<<1],ac[N<<1];
vector<node> vb[N],vc[N];
int gb[N],gc[N];
void solve()
{
    int INF =1e9;
    cin>>n;


//    for(int i=0;i<10;i++) cerr<<tr[i]<<' ';
    for(int i=1;i<=n;i++){
        cin>>sa[i]>>sb[i]>>sc[i];
        sa[i]+=sa[i-1];
        sb[i]+=sb[i-1];
        sc[i]+=sc[i-1];
        sab[i]=sa[i]+n+1-sb[i];
        sac[i]=sa[i]+n+1-sc[i];
    }



    
    for(int i=1;i<=n;i++){
        vb[sab[i]].push_back({i,sab[i],sac[i]});
        vc[sac[i]].push_back({i,sab[i],sac[i]});
    }
    for(int i=1;i<=2*n+1;i++){
        sort(vb[i].begin(),vb[i].end(),cmp1);
        sort(vc[i].begin(),vc[i].end(),cmp2);
        int sb=vb[i].size(),sc=vc[i].size();
        for(int j=0;j<=sb;j++) ab[i].tr.push_back(-INF);
        for(int j=0;j<=sc;j++) ac[i].tr.push_back(-INF);
        for(int j=0;j<sb;j++) gb[vb[i][j].id]=j+1;
        for(int j=0;j<sc;j++) gc[vc[i][j].id]=j+1;

    }


    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        if(sa[i]>=sb[i]&&sa[i]>=sc[i]) dp[i]=i;
    //    cout<<gb[i]<<gc[i]<<endl;
    //    continue;
        //cout<<ab[i].tr.size()<<' '<<gb[i]<<endl;
    //    continue;
        
        dp[i]=max(dp[i],ab[sab[i]].query(gb[i])+i);
        dp[i]=max(dp[i],ac[sac[i]].query(gc[i])+i);

        //

       ab[sab[i]].add(gb[i],dp[i]-i);
       ac[sac[i]].add(gc[i],dp[i]-i);
      // cout<<dp[i]<<endl;
    }


    cout<<dp[n];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}