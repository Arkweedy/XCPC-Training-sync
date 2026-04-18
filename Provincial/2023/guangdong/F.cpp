#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

#define ls p<<1
#define rs p<<1|1
using namespace std;

//Create time: 2026.04.10 10:09:19
constexpr int N =1e5+10;
int n,q,nc[N],nv[N];
struct Q{
    int op,p,x,k;
    vector<int> ve;
    Q():ve(5, 1){}
    
}que[N];
ll ans[N];
struct tre{
    int n,a[N];
    ll s[N<<2];
    int mi[N<<2];
    void build(int p,int l,int r){
        if(l==r){mi[p]=s[p]=a[l];return ;}
        int m=l+r>>1;
        build(ls,l,m);build(rs,m+1,r);
        s[p]=s[ls]+s[rs];
        mi[p]=min(mi[ls],mi[rs]);
    }
    ll query(int p,int l,int r,int jl,int jr){
        if(jl<=l&&r<=jr) return s[p];
        int m=l+r>>1;
        ll ans=0;
        if(jl<=m) ans+=query(ls,l,m,jl,jr);
        if(jr>m) ans+=query(rs,m+1,r,jl,jr);
        return ans;
    }
    void update(int p,int l,int r,int x,int k){
        if(l==r){s[p]=mi[p]=k;return ;}
        int m=l+r>>1;
        if(x<=m) update(ls,l,m,x,k);
        else update(rs,m+1,r,x,k);
        s[p]=s[ls]+s[rs];
        mi[p]=min(mi[ls],mi[rs]);
    }
    int queryl(int p,int l,int r,int jl,int jr,int k){
        if(mi[p]>=k) return -1;
        if(jl>r||jr<l) return -1;
        if(l==r) return l;
        int m=l+r>>1;
        int a=queryl(ls,l,m,jl,jr,k);
        if(a>0) return a;
        return queryl(rs,m+1,r,jl,jr,k);
    }
}tc,tv;
set<int> s[N];
int l[N];
int c[N];
void deal(int pp){
    //for(int i=1;i<=n;i++) ans[i]=0;
    tc.n=tv.n=n;
    for(int i=1;i<=n;i++) s[i].clear(),c[i]=nc[i];
    for(int i=1;i<=n;i++) s[nc[i]].insert(i);
    for(int i=1;i<=n;i++){
        auto it=s[nc[i]].lower_bound(i);
        if(it==s[nc[i]].begin()) l[i]=-1;
        else it--,l[i]=*it;
    }
    for(int i=1;i<=n;i++) tc.a[i]=l[i],tv.a[i]=nv[i];
    tc.build(1,1,n);tv.build(1,1,n);
    for(int i=1;i<=q;i++){
        if(que[i].op==1){
            int p=que[i].p,x=que[i].x;
            int nc=c[p];
            auto it=s[nc].lower_bound(p);
            s[nc].erase(it);
            it=s[nc].lower_bound(p);
            if(it!=s[nc].end()){
                int g=*it;
                if(it==s[nc].begin()) l[g]=-1;
                else
                {
                    it--;
                    l[g]=*it;
                }
                tc.update(1,1,n,g,l[g]);
            }

            s[x].insert(p);
            it=s[x].lower_bound(p);
            if(it==s[x].begin()) l[p]=-1;
            else {
                it--;
                l[p]=*it;
            }
            tc.update(1,1,n,p,l[p]);

            it=s[x].lower_bound(p);
            it++;
            if(it!=s[x].end()){
                l[*it]=p;
                tc.update(1,1,n,*it,p);
            }
            c[p]=x;
        }
        else if(que[i].op==2){
            tv.update(1,1,n,que[i].p,que[i].x);
        }
        else {
            int x=que[i].x,k=que[i].k;
            map<int,int> mp;
            for(auto p:que[i].ve) mp[p]=1;
            int r=x;
            int cnt=0;
            while(r<n){
            //    cerr<<r<<endl;
                int s=tc.queryl(1,1,n,r+1,n,x);
            //    cerr<<s<<endl;
                if(s==-1) r=n;
                else {
                    if(!mp.count(c[s])) {r=s-1;break;}
                    r=s; 
                }
                cnt++;
                //if(cnt>2*k) assert(0);
            }
        //    if(i==10 ) for(int i=1;i<=n;i++) cerr<<c[i]<<' '<<l[i]<<' '<<tc.query(1,1,n,i,i)<<endl;
          //  if(i==10) cerr<<x<<' '<<r<<endl;
            //cerr<<r<<endl;
        //    cerr<<endl;
            ans[i]+=tv.query(1,1,n,x,r);
            if(pp==1) ans[i]-=tv.query(1,1,n,x,x);
        }
    }
}
void solve()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) ans[i]=0;
    for(int i=1;i<=n;i++) cin>>nc[i];
    for(int i=1;i<=n;i++) cin>>nv[i];
    for(int i=1;i<=q;i++) {
        cin>>que[i].op;
        if(que[i].op<=2) cin>>que[i].p>>que[i].x;
        else {
            cin>>que[i].x>>que[i].k;
            que[i].ve.clear();
            for(int j=0;j<que[i].k;j++){
                int s;cin>>s;
                que[i].ve.push_back(s);
            }
        }
    }
    deal(0);
    reverse(nc+1,nc+n+1);
    reverse(nv+1,nv+n+1);
    for(int i=1;i<=q;i++) 
    {
        if(que[i].op<=2) que[i].p=n+1-que[i].p;
        else {
            que[i].x=n+1-que[i].x;
        }
    }
    deal(1);
    for(int i=1;i<=q;i++)
        if(que[i].op==3) cout<<ans[i]<<'\n';
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