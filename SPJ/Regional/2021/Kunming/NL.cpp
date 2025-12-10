#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

#define lowbit(x) ((x)&(-x))

using namespace std;

const int N = 1e5 + 10;

using ld = long double;
const ld PI = acos(-1),eps = 1e-10;


int n,k,ans[N];
int l,r,x[N],y[N];
ld xl,yl,xr,yr,u[N],v[N];
int s[N],m;

void add(int x,int t){
    while(x<=m){
        s[x] += t;
        x += lowbit(x);
    }
}

int query(int x){
    int res = 0;
    x = min(x,m);
    while(x){
        res += s[x];
        x-=lowbit(x);
    }
    return res;
}

void calc(){
    vector<ld>b;
    vector<int>p(n);
    for(int i=1;i<=n;i++){
        u[i] = x[i] * yl - y[i] * xl;
        v[i] = x[i] * yr - y[i] * xr;
        p[i-1] = i;
        b.push_back(v[i]);
    }
    sort(p.begin(),p.end(),[&](int x,int y){
        return u[x] < u[y];
    });
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    m = b.size();
    for(int i=1;i<=m;i++)s[i] = 0;
    for(auto k:p){
        int t = lower_bound(b.begin(),b.end(),v[k]) - b.begin() + 1;
        ans[k] += query(m) - query(t);
        add(t,1);
    }
}

void solve()
{
    
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    while(k--){
        cin>>l>>r;
        l = 180-l,r = 180-r;
        swap(l,r);
        if(l==r){
            ld x1 = PI * l / 180, y1 = PI * r / 180;
            xl = cosl(x1),yl = sinl(x1);
            xr = cosl(y1),yr = sinl(y1);
            for(int i=1;i<=n;i++){
                a[i].x = x[i] * yl - y[i] * xl;
                a[i].y = x[i] * xl + y[i] * yl;
                a[i].y = -a[i].y;
            }

            sort(p.begin()+1,p.end(),[&](int x,int y){
                return u[x] < u[y];
            });
            

            int cnt = 0;
            for(int i=1;i<=n;){
                int j = i;
                while(j<=n && u[p[j]] - u[p[i]] <= eps){
                    j++;
                }
                for(int k=i;k<j;k++){
                    ans[p[k]] += cnt + j - i - 1;
                }
                cnt += j - i;
                i = j;
            }

            continue;
        }
        //cout<<l<<' '<<r<<endl;
        ld x = PI * l / 180 - eps, y = PI * r / 180 + eps;
        xl = cosl(x),yl = sinl(x);
        xr = cosl(y),yr = sinl(y);
        //cout<<xl<<' '<<yl<<' '<<xr<<' '<<yr<<endl;
        calc();
    }
    for(int i=1;i<=n;i++)cout<<ans[i]<<" \n"[i==n];
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}