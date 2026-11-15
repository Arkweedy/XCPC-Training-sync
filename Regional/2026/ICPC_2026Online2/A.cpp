#include<bits/stdc++.h>
#define N 2000009

using i64 = long long;
using ll = long long;
using namespace std;
int n;
struct bit{
    int a[20],cnt;
    bit(){
        memset(a,0,sizeof(a));
        cnt=0;
    }
    void add(int p){
        for(int i=19;i>=0;i--){
            if(p>>i&1){
                if(!a[i]){
                    a[i]=p;cnt++;return ;
                }
                p^=a[i];
            }
        }
    }
    int check(int p){
        for(int i=19;i>=0;i--){
            if(p>>i&1){
                if(!a[i]){
                    return 0;
                }
                p^=a[i];
            }
        }
        return 1;
    }
};
vector<int> a[N];
int vis[N],cnt[N];
bit b[N];
bit ans;
vector<int> out;
void output(bit a){
    vector<int> ve;
    for(int i=0;i<20;i++) 
        if(a.a[i]) ve.push_back(a.a[i]);
    for(int i=0;i<(1<<ve.size());i++){
        int t=0;
        for(int j=0;j<ve.size();j++) 
            if(i>>j&1) t^=ve[j];
        if(cnt[t]<n) out.push_back(t);
    }
}
int bshua[N];
int ashub[N][20];
void print(bit a){
    for(int i=0;i<20;i++)
        if(a.a[i])  cout<<a.a[i]<<endl;
}
void solve()
{
    //ans.add(0);ans.add(1);ans.add(7);cout<<ans.cnt;
    int m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int num;cin>>num;
        for(int j=1;j<=num;j++){
            int x;cin>>x;
            
            vis[x]=1;a[i].push_back(x);cnt[x]++;
            b[i].add(x);
        }
        int g=b[i].cnt;
        
        if(num*2<(1<<g)){
            for(int j=0;j<20;j++)
                if(b[i].a[j]) ans.add(b[i].a[j]);
        }
        else {
                vector<int> ve;
            for(int j=0;j<20;j++)
            if(b[i].a[j]) ve.push_back(b[i].a[j]);
            for(int j=0;j<(1<<g);j++){
                int t=0;
                for(int k=0;k<g;k++)
                    if(j>>k&1) t^=ve[k];
                if(vis[t]) continue;
                ans.add(t);
            }
            
        }
        for(auto p:a[i]) vis[p]=0;
    }
    // cout<<endl;
    // print(ans);
    // return ;

    while(1){
        int now=ans.cnt;
        for(int i=1;i<=n;i++){
            if(bshua[i]) continue;

            for(int j=0;j<20;j++){
                if(ans.a[j]&&!ashub[i][j]){
                    int st=b[i].check(ans.a[j]);
                    if(st==0){
                        
                        for(int j=0;j<20;j++)
                            if(b[i].a[j]) ans.add(b[i].a[j]);
                        bshua[i]=1;
                        break;
                    }
                    else {
                        //ajshub
                        ashub[i][j]=1;
                    }
                } 
            }
        }

        if(ans.cnt==now) break;
    }


    output(ans);
    cout<<out.size()<<'\n';
    for(auto p:out) cout<<p<<' ';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
//    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}



