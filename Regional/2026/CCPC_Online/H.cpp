#include<bits/stdc++.h>
#define N 2009
using i64 = long long;
using ll = long long;

using namespace std;
int n;
map<vector<int> ,int> mp;
void output(vector<vector<int> > a){
    for(auto ve:a){
        for(auto p:ve) cout<<p<<' ';
        cout<<'\n';
    }
}
void solve()
{
    int op;
    string s;cin>>s;
    if(s[0]=='f') op=1;
    else op=2;
    cin>>n;
    
    vector<int> a;
    for(int i=1;i<=n;i++) a.push_back(i);

    for(int i=1;i<=n;i++){
        for(int j=0;j<n;j++){
            a[j]++;
            if(a[j]>n) a[j]=1;
        }
        mp[a]=3;
    }
    mp[a]=1;
        vector<int> b;
    for(int i=n;i;i--) b.push_back(i);

    for(int i=1;i<=n;i++){
        for(int j=0;j<n;j++){
            b[j]++;
            if(b[j]>n) b[j]=1;
        }
        mp[b]=2;
    }
    
    if(op==1){
        vector<vector<int> > ans;
        vector<int> p;
        for(int i=0;i<n;i++){
            int x;cin>>x;p.push_back(x);
        }
        if(mp[p]==1||mp[p]==3){
            int g=p[0];

            for(int i=0;i<g;i++){
                for(int j=0;j<n;j++){
                    b[j]++;
                    if(b[j]>n) b[j]=1;
                
                }
                ans.push_back(b);
            }
            vector<int> pp;
            for(int i=1;i<=n;i++) pp.push_back(i);
            //cout<<ans.size()<<endl;
            do{

                if(mp[pp]==1||mp[pp]==2) continue;
                if(ans.size()==n) break;
                ans.push_back(pp);
            }while(next_permutation(pp.begin(),pp.end()));
            assert(ans.size()==n);
            //output(ans);
        }

        else {
            ans.push_back(a);
            for(int j=1;j<n;j++){
                for(int jj=0;jj<n;jj++){
                    p[jj]++;
                    if(p[jj]>n) p[jj]=1;
                    
                }
                ans.push_back(p);
            }
        }
        output(ans);
    }
    else {
        vector<vector<int> > input,in;
        for(int i=1;i<=n;i++){
            vector<int> ve;
            for(int i=1;i<=n;i++){
                int x;cin>>x;ve.push_back(x);
            }
            input.push_back(ve);
        }
        int opp=0;
        for(auto ve:input){
            if(mp[ve]==1) opp=1;
            else in.push_back(ve);
        }
        if(opp==0){
            int cnt=0;
            for(auto ve:input)
                cnt+=(mp[ve]==2);
            for(int i=cnt;i<cnt+n;i++){
                int g=i;
                if(g>n) g-=n;
                cout<<g<<' ';
            }
        }
        else {


            int vis[2009];
            memset(vis,0,sizeof(vis));
            int t=0;
            for(int i=1;i<=n;i++) t+=i;
            for(int i=0;i<n;i++){
                int s=t;
                for(int j=0;j<n-1;j++) s-=in[j][i];
                cout<<s<<' ';
            }
            
        }


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

