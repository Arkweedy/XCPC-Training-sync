#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
using ll = long long;


using namespace std;

constexpr int N = 5e5 + 10;

int n,m,sz,x[N];
ll s[N],c[N],f[N];
vector<int>b;
void add(int x,int t,ll v){
    while(x<=sz){
        c[x] += t;
        s[x] += v;
        x += lowbit(x);
    }
}


pair<ll,ll> query(int x){
    ll res1 = 0,res2 = 0;
    while(x){
        res1 += c[x];
        res2 += s[x];
        x -= lowbit(x);
    }
    return {res1,res2};
}

void solve()
{
    cin>>n>>m;
    b.push_back(0);
    for(int i=1;i<=n;i++){
        cin>>x[i];
        b.push_back(x[i]);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    sz = b.size() - 1;

    for(int i=1;i<=n;i++){
        int y = lower_bound(b.begin(),b.end(),x[i]) - b.begin();
        auto [c,s] = query(y);
        f[i] += c * x[i] - s + c;
        add(y,1,x[i]);
    }

    for(int i=1;i<=n;i++)c[i] = s[i] = 0;
    for(int i=n;i;i--){
        int y = lower_bound(b.begin(),b.end(),x[i]) - b.begin();
        auto [c,s] = query(y);
        f[i] += c * x[i] - s;
        add(y,1,x[i]);
    }

    for(int i=1;i<=n;i++){
        if(f[i] > m-2)cout<<-1<<'\n';
        else cout<<f[i]<<'\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}