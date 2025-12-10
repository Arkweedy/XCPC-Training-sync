#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 5e4 + 10;

int n,a[N],b[N],c[N];
bool st[N];
void solve()
{
    cin>>n;
    string s;cin>>s;
    for(int i=1;i<=n;i++){
        if(s[i-1] == '0')a[i] = - 1;
        else a[i] = 1;
        st[i] = c[i] = 0;
    }
    cin>>s;
    for(int i=1;i<=n;i++)b[i] = s[i-1] - '0';
    int cur = 0; 
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            c[j] += a[j-i+1];
            cur -= st[j];
            st[j] = (c[j] <= 0) ^ (b[j]);
            cur += st[j];
        }
        if(cur == n)cout<<1;
        else cout<<0;
    }


    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}