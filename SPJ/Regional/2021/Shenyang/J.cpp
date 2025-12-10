#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
constexpr int INF=1e9;
int d[N];
void pre()
{
    for(int i=1;i<N;i++) d[i]=INF;
    string s="0000";
    queue<string> q;
    q.push(s);
    while(q.size())
    {
        string s=q.front();q.pop();
        int t=stoi(s);t=d[t];
        for(int p=0;p<=1;p++)
            for(int i=0;i<=3;i++)
                for(int j=i;j<=3;j++)
            {
                string ss=s;
                for(int k=i;k<=j;k++)
                {
                    if(p) ss[k]++;
                    else ss[k]--;
                    if(ss[k]<'0') ss[k]+=10;
                    if(ss[k]>'9') ss[k]-=10;
                }
                int tt=stoi(ss);
                if(d[tt]==INF)
                {
                    d[tt]=t+1;
                    q.push(ss);
                }
            }
    }
}
void solve()
{
    string s,ss;
    cin>>s>>ss;
    for(int i=0;i<4;i++)
    {
        if(ss[i]<s[i]) ss[i]+=10;
        ss[i]-=s[i];
        ss[i]+='0';
    }
    int t=stoi(ss);
    cout<<d[t]<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    pre();
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
}