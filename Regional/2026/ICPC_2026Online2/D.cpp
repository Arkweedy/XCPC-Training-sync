#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;
using namespace std;
const int N = 18;
int t[(1 << N+1) + 9];
int p[(1 << N)+1 + 9];

const ll M = 998244353;
vector<int> pos[(1 << N)+1 + 9];
bool mark = true;
int cntt[(1 << N)+1 + 9];
int maxone[(1 << N)+1 + 9];
int sl[(1 << N+1) + 9];
int sr[(1 << N+1)+ 9];
void f(int pos,int l,int r)
{
    sl[pos] = l,sr[pos] = r;
    if(l != r)
    {
        int mid = l + r >> 1;
        f(pos<<1,l,mid);
        f(pos<<1|1,mid+1,r);
    }
    if(t[pos])
    {
        bool isadd = false;
        for(int i = l;i <= r;i++)
        {
            if(p[i] == 0)
            {
                p[i] = t[pos];
                cntt[t[pos]]++;
                isadd = true; 
            }        
            else if(p[i] > t[pos])
            {
                mark = false;
            }

            if(p[i] == t[pos])
            {
                isadd = true;
            }
        }
        if(!isadd) mark = false;
    }
}
void solve()
{
    int n,q;
    cin >> n >> q;

    while(q--)
    {
        int u,x;
        cin >> u >> x;
        if(t[u] == 0)
        {
            t[u] = x;
            pos[x].push_back(u);
        }
        else if(t[u] != x)
        {
            mark = false;
        }
    }
    int u = 1,x = 1 << n;
    if(t[u] == 0)
    {
        t[u] = x;
        pos[x].push_back(u);
    }
    else if(t[u] != x)
    {
        mark = false;
    }

    for(int i = 1;i <= (1 << n);i++)
    {
        if(!pos[i].empty())
        {
            sort(pos[i].begin(),pos[i].end());
            maxone[i] = pos[i].back();
            for(int j = 0;j < pos[i].size() - 1;j++)
            {
                int temp = pos[i][j + 1];
                while(temp != 0 && temp != pos[i][j]) temp >>= 1;
                if(temp == 0)
                {
                    mark = false;
                }
            }
        }
    }
    f(1,1,1 << n);

    ll ans = 1ll;
    ll cnt = 0;
    
    for(int i = (1 << n);i >= 1;i--)
    {
        if(!pos[i].empty())
        {
            ll cnttt = 0;
            
            for(int j = sl[maxone[i]];j <= sr[maxone[i]];j++)
            {
                if(p[j] == i) cnttt++;
            }
            //cerr << i << ' ' << cntt << '\n';
            ans = 1ll * ans * cnttt % M;
            cnt += cntt[i] - 1;
        }
        else
        {
            //err << i << " | " << cnt << '\n';
            ans = 1ll * ans * cnt % M;
            cnt--;
        }
    }
    if(mark) cout << ans << '\n';
    else cout << 0 << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}



