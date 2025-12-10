#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
int n;string s;

string f(string s)
{
    int tot[200];
    int cnt=0;
    memset(tot,0,sizeof(tot));
    int len=s.length();
    for(int i=len-1;i>=0;i--)
    {
        if(!tot[s[i]])
        {
            tot[s[i]]=cnt+'a';
            cnt++;
        }
    }
    for(int i=0;i<len;i++) s[i]=tot[s[i]];
    return s;
}
void solve()
{
    string ans;
    cin>>n;
    char c;
    for(int i=1;i<=n;i++)
    {
        cin>>c;s+=c;
        ans=max(ans,f(s));
    }
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
}