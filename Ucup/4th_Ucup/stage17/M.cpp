#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;
using pii = pair<int,int>;
const int N = 1e4 + 9;
int a,b,m;
int be[N],en[N],ty[N];
int cnt;
int cnt1[N];
int cnt2[N];
vector<int> adj[N];
int de[N];
int la[N];
void solve()
{
    cin >> a >> b >> m;
    for(int i = 1;i <= m;i++)
    {
        cin >> ty[i] >> be[i] >> en[i];
        adj[i].clear();
        cnt1[i] = cnt2[i] = de[i] = 0;
    }
    cnt = 0;
    for(int i = 1;i <= m;i++)
    {
        for(int j = i + 1;j <= m;j++)
        {
            if(be[j] > en[i])
            {
                adj[j].push_back(i);
                de[i]++;
            }
            else if(be[i] > en[j])
            {
                adj[i].push_back(j);
                de[j]++;
            }
        }
    }
    vector<int> q;
    for(int i = 1;i <= m;i++)
    {
        if(de[i] == 0)
        {
            q.push_back(i);
        }
    }
    vector<int> temp;
    while(!q.empty())
    {
        cnt++;
        temp.clear();
        while(!q.empty())
        {
            int x = q.back();
            q.pop_back();
            la[x] = cnt;
            for(const int num : adj[x])
            {
                de[num]--;
                if(de[num] == 0)
                {
                    temp.push_back(x);
                }
            }
        }
        q = temp;
    }
    for(int i = 1;i <= m;i++)
    {
        if(ty[i] == 1)
        {
            cnt1[la[i]]++;
        }
        else cnt2[la[i]]++;
    }
    int ans = 0;
    for(int i = 1;i <= cnt;i++)
    {
        ans = max(ans,cnt2[i] + max(0,cnt1[i] - b));
    }
    if(a >= ans)cout << "Yes\n";
    else cout << "No\n";

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
