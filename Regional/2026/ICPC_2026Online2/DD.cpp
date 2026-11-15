#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;
using namespace std;
const int N = 18;
int t[1 << (N+1) + 9];
int p[(1 << N)+1 + 9];

const ll M = 998244353;
vector<int> pos[(1 << N)+1 + 9];
bool mark = true;
int cntt[(1 << N)+1 + 9];
int maxone[(1 << N)+1 + 9];
void f(int pos,int l,int r)
{
    if(l != r)
    {
        int mid = l + r >> 1;
        f(pos<<1,l,mid);
        f(pos<<1|1,mid+1,r);
    }
    if(t[pos] && maxone[t[pos]] == pos)
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
            int minone = (1 << n + 1) - 1;
            for(const auto num : pos[i]) 
            {
                minone = min(minone,num);
                maxone[i] = max(maxone[i],num);
            }
            for(const auto xx : pos[i])
            {
                int num = xx;
                while(num != 0 && num != minone)
                {
                    num >>= 1;
                }
                if(num == 0)
                {
                    mark = false;
                }
            }
        }
    }
    f(1,1,1 << n);
    ll ans = 1ll;
    ll cnt = 0;
    for(int i = 1;i <= (1 << n);i++)
    {
        if(p[i] == 0)
        {
            int cur = i + (1 << n) - 1;
            while(t[cur] == 0) cur >>= 1;
            p[i] = t[cur] - 1;
            cntt[t[cur] - 1]++;
        }
    }
    for(int i = (1<<n);i >= 1;i--)
    {
        cnt += cntt[i];
        ans = ans * cnt;
        cnt--;
    }
    if(mark)
        cout << ans << '\n';
    else
        cout << 0 << '\n';
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



