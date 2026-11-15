#include<bits/stdc++.h>
#define N 500009
using ll = long long;
using i64 = long long;

using namespace std;
int n,m,q;
struct node{
    int o,x;
}a[N];

int ne[N][2];
int nex[2][N][22];
int r[2][N];
int tt[N];
void solve()
{
    
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        cin>>a[i].o>>a[i].x;
    }

    
    reverse(a+1,a+m+1);

    multiset<int> s[2];
    s[0].insert(0);s[1].insert(n+1);
    int rr=m;
    for(int i=m;i;i--){

        auto [o,x]=a[i];
        s[o].insert(x);
        while(rr>=i){
            auto it=s[0].end(),itt=s[1].begin();
            it--;
            if(*it>=*itt-1) s[a[rr].o].erase(s[a[rr].o].lower_bound(a[rr].x)),rr--;
            else break;
        }
        tt[i]=rr;
    }


    
    ne[m+1][0]=ne[m+1][1]=m+1;
    for(int i=m;i;i--){
        ne[i][0]=ne[i+1][0];
        ne[i][1]=ne[i+1][1];
        ne[i][a[i].o]=i;
    }
    


    for(int i=m;i;i--){
        auto [o,x]=a[i];
        if(!o){
            int j=ne[i+1][o];
            while(j<=m&&a[j].x<=x) j=r[o][j];
            r[o][i]=j;
        }
        else {
            int j=ne[i+1][o];
            while(j<=m&&a[j].x>=x) j=r[o][j];
            r[o][i]=j;
        }
    }

    for(int i=1;i<=m;i++) 
        for(int o=0;o<2;o++) nex[o][i][0]=r[o][i];

    //for(int i=1;i<=m;i++)  cout<<nex[1][i][0]<<endl;
    
    nex[0][m+1][0]=nex[1][m+1][0]=m+1;

    for(int i=m+1;i;i--)
        for(int k=1;k<22;k++){
            for(int o=0;o<2;o++) nex[o][i][k]=nex[o][nex[o][i][k-1]][k-1];
        }


            
    while(q--){
        int l,r;cin>>l>>r;
        l=m+1-l,r=m+1-r;
        swap(l,r);

        int ans=0;
        int pl=min(r,tt[l]);

    //    cout<<1;return ;
    //   cout<<pl<<endl;

        if(pl<r) ans++;
        for(int o=0;o<2;o++){
            int p=ne[l][o];
            //cout<<p<<endl;
            if(p>pl) continue;
            ans++;
            for(int k=21;k>=0;k--){
                int q=nex[o][p][k];
                //cout<<p<<' '<<q<<endl;
                if(q<=pl) {
                    p=q;
                    ans+=(1<<k);
                }
            }
        }
        cout<<ans<<'\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}