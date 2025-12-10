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
ld xl,yl,xr,yr;
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


bool check(ld x,ld y){
    return abs(x-y) < eps;
}

struct Point {
    ld x,y;
    int id;
}a[N];

bool operator < (const Point &a,const Point &b){
    if(check(a.x,b.x))return a.y < b.y;
    return a.x < b.x;
}

bool operator == (const Point &a,const Point &b){
    return check(a.x,b.x) && check(a.y,b.y);
}

void calc(){
    vector<ld>b;

    for(int i=1;i<=n;i++){
        b.push_back(a[i].y);
    }
    sort(a+1,a+n+1);
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end(),check),b.end());
    m = b.size();

    for(int i=1;i<=m;i++)s[i] = 0;
    for(int i=1;i<=n;i++){

        int t = lower_bound(b.begin(),b.end(),a[i].y) - b.begin();
        for(int j=t-5;j<=t+5;j++){
            if(j < 0 || j >= m)continue;
            if(check(b[j],a[i].y)){
                t = j + 1;
                break;
            }
        }
        ans[a[i].id] += query(t);
        add(t,1);
    }
}

void solve()
{
    
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }''
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
                a[i].id = i;
            }

            sort(a+1,a+n+1);
            for(int i=1;i<=n;){
                int j = i;
                while(j <= n && check(a[i].x,a[j].x))j++;
                for(int k=i;k<j;k++){
                    ans[a[k].id] += k - i;
                }
                i = j;
            }
            continue;
        }
        else{
            ld x1 = PI * l / 180, y1 = PI * r / 180;
            xl = cosl(x1),yl = sinl(x1);
            xr = cosl(y1),yr = sinl(y1);
            for(int i=1;i<=n;i++){
                a[i].x = x[i] * yl - y[i] * xl;
                a[i].y = x[i] * yr - y[i] * xr;
                a[i].y = -a[i].y;
                a[i].id = i;
            }
        }

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