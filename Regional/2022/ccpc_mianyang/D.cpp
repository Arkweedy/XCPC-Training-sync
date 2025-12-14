#include<bits/stdc++.h>
using ll = long long;
using namespace std;

using ld = long double;
using i128 = __int128;
constexpr int N = 1e6 + 10,M = 1e6;

struct Node{
    ll p,c;
    bool operator < (const Node &a){
        return p < a.p;
    }
}a[N],b[N],c[N];
int n,m;

ll s[N];

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;cin>>s;
        cin>>a[i].c;
        if(s== "1")a[i].p = M;
        else if(s == "0")a[i].p = 0;
        else {
            a[i].p = s[0] - '0';
            for(int j=0;j<6;j++){
                if(j+2<s.size())a[i].p = a[i].p * 10 + s[j+2] - '0';
                else a[i].p *= 10;
            }
            
        }
    }
    sort(a+1,a+n+1); 
    m = 0;   
    for(int i=1;i<=n;i++){
        if(m && a[i].p == b[m].p){
            b[m].c += a[i].c;
        }
        else{
            b[++m] = a[i];
        }
    }
    for(int i=1;i<=m;i++){
        c[i] = b[m-i+1];
    }
    /*
    c x
    b y
    */
    for(int i=1;i<=m;i++)s[i] = s[i-1] + b[i].c;

    ld res = 0;

    ll sum = 0;
    for(int i=1;i<=m;i++){
        if(c[i].p == 0)break;
        sum += c[i].c;

        if(i!=m){
            int l = 1,r = m-i;
            while(l<r){
                int mid = l+r+1>>1;
                if((i128)s[mid] * c[i].p <= (i128)sum * (M-b[mid].p))l = mid;
                else r = mid-1;
            }
            for(int j=l-5;j<=l+5;j++){
                if(j <= 0 || j > m-i)continue;
                //cout<<i<<' '<<j<<endl;
                res = max(res,sum + s[j] - max(sum * 1.0L * M /c[i].p,s[j] *1.0L * M/(M-b[j].p)));
            }
        }
    }
    cout<<fixed<<setprecision(10);
    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while (tt--)
    {
        solve();
    }
    return 0;    
}
