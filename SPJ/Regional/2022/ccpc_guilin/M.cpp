#include<bits/stdc++.h>

#define lowbit(x) (x&(-x))
using ll = long long;
using namespace std;

constexpr int N = 3e5 + 10;
int n,m;
int bit[N];

void add(int x,int t){
    while(x<=n){
        bit[x] += t;
        x += lowbit(x);
    }
}

int query(int x){
    int res = 0;
    while(x){
        res += bit[x];
        x -= lowbit(x);
    }
    return res;
}

void solve()
{
    cin>>n>>m;
    vector<int>p(n+1);
    ll cur = 0;
    for(int i=0;i<n;i++){
        cin>>p[i];
        cur += query(n) - query(p[i]);
        add(p[i],1);
    }
    int i = 0;
    cout<<cur<<'\n';
    string s;cin>>s;
    int op = 1;
    for(auto c:s){
        if(c == 'S'){
            cur += - (p[i]-1) + (n-p[i]);
            i = (i+op+n)%n;
        }else{
            cur = 1ll * n * (n-1)/2 - cur;
            op *= -1;
            i = (i+op+n)%n;
        }
        cout<<cur % 10;
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