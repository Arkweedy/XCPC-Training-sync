#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e6 + 10;
int n,d;
int h[N];
struct node{int id;ll w;};
void solve()
{
    ll sum=0;
    cin>>n>>d;
    for(int i=1;i<=n;i++) cin>>h[i],sum+=h[i];
    int tar=sum/n;
    //cout<<sum<<endl;
    int maxd=0;
    queue<node> q;
    for(int i=1;i<=n;i++)
    {
        ll g=h[i]-tar;
        int op=0;
        if(g<0) op=-1;
        else if(g>0) op=1;
        if(!op) continue;
        if(q.size())
        {
            if(q.front().w * op>0) q.push({i,g}),g=0;
            else 
            {
                while(q.size() && g)
                {
                    auto no = q.front();
                    if(abs(no.w) <= abs(g))
                    {
                        g += no.w;
                        maxd = max(maxd,i-no.id);
                        q.pop();
                    }
                    else{
                        q.front().w  += g;
                        g = 0;
                        maxd=max(maxd,i-no.id);
                    }
                }
            }
        }
        if(g) q.push({i,g});
    }
    assert(q.empty());
    cout<<(maxd+d-1)/d<<'\n';
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