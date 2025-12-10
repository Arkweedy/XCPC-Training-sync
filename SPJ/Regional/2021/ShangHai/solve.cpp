#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 5e4 + 10;

bitset<N> f[N],g,ans,t;
int n,s[N];
string a,b;
void solve()
{
    cin>>n>>a>>b;
    a = ' ' + a;
    b = ' ' + b;
    int mi = n;
    for(int i=1;i<=n;i++){
        s[i] = a[i] == '0' ? -1 : 1;
        s[i] += s[i-1];
    }

    for(int i=0;i<=n;i++)mi = min(mi,s[i]);
    for(int i=0;i<=n;i++)f[s[i]-mi].reset();
    for(int i=0;i<=n;i++){
        f[s[i]-mi][n-i] = 1;
    }

    if(s[1] > 0 && b[1] == '1')ans.set();
    else if(s[1] <= 0 && b[1] == '0')ans.set();
    else ans.reset();

    if(s[1] > 0)g.set();
    else g.reset();

    // g 记录哪些长度是正的。
    for(int i=2;i<=n;i++){
        g <<= 1;
        if(a[i] == '0'){
            int pos = s[i] - mi;
            t = f[pos] >> (n-i);

            t.flip();
            t[1] = 0;
            g &= t;
        }else{
            int pos = s[i-1] - mi;
            t = f[pos] >> (n-i);
            g |= t;
        }

        

        t.set();
        if(s[i] > 0){
            t <<= i;
            g |= t;
        }else{
            t >>= (N-i);
            g &= t;
        }

        if(b[i] == '0'){
            t = g;
            t.flip();
            ans &= t;
        }
        else {
            ans &= g;
        }

        
    }

    for(int i=1;i<=n;i++)cout<<ans[i];
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