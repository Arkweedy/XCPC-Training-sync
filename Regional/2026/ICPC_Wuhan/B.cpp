#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;
using a3 = array<int,3>;
using pii = pair<int,int>;
const int N = 2e5 + 9;
vector<int> x[N];
int d;
int cnt[N];
a3 ck(a3 x,a3 y)
{
    if(x[2] != y[2])
    {
        if(x[2] > y[2]) return x;
        else return y;
    }
    if(x[0] != y[0])
    {
        if(x[0] < y[0]) return x;
        else return y;
    }
    if(x[1] < y[1]) return x;
    return y;

}
void solve()
{
    cin >> d;
    for(int i = 1;i <= d;i++) x[i].clear();
    int maxlen = 0;
    for(int i = 1;i <= d;i++)
    {
        string n;
        cin >> n;
        for(const char ch : n)
        {
            x[i].push_back(ch - '0');
        }
        reverse(x[i].begin(),x[i].end());
        maxlen = max(maxlen,(int)x[i].size());
    }
    int k = max(1,maxlen - 26);
    map<pii,int> ma;
    for(int i = 1;i <= d;i++)
    {
        int la = -1;
        for(int j = 0;j <= k - 2 && j < x[i].size();j++)
        {
            if(x[i][j])
            {
                if(la != -1)
                {
                    ma[{j,la}]++;
                }
                la = j;
            }
        }
    }
    a3 curx = {0,0,0};
    for(const auto [a,b] : ma)
    {
        a3 te = {a.first,a.second,b};
        curx = ck(curx,te);
    }

    while(k <= maxlen + 1)
    {
        int num = 0;
        a3 te = curx;
        for(int i = 1;i <= d;i++)
        {
            if(x[i].size() >= k)
            {
                for(int j = k - 2;j >= 0;j--)
                {
                    if(x[i][j])
                    {
                        cnt[j]++;
                        break;
                    }
                }
                int cur = 0;
                for(int j = x[i].size() - 1;j >= k - 1;j --)
                {
                    cur *= 2;
                    cur += x[i][j];
                }
                num += cur - 1;
                num = min(num,(int)1e8);
            }            
        }
        for(int j = 0;j <= k-2;j++)
        {
            a3 tt = {k-1,j,cnt[j]};
            te = ck(te,tt);
        }
        if(te[2] >= num && te[2] > 0)
        {
            cout << k-1 << ' ' <<  te[0] << ' ' << te[1] << ' ' << te[2] << '\n'; 
            for(int j = 0;j <= k-2;j++)
            {
                cnt[j] = 0;
            }
            return;
        }
        else 
        {
            for(int i = 0;i <= k - 2;i++) cnt[i] = 0;
            for(int i = 1;i <= d;i++)
            {
                if(x[i].size() >= k)
                {
                    if(x[i][k-1])
                    {
                        for(int j = k - 2;j >= 0;j--)
                        {
                            if(x[i][j])
                            {
                                cnt[j]++;
                                break;
                            }
                        }
                        
                    }
                }   
            }
            for(int i = 0;i <= k - 2;i++) 
            {
                a3 tt = {k-1,i,cnt[i]};
                curx = ck(curx,tt);
            }
            for(int i = 0;i <= k - 2;i++) cnt[i] = 0;
        }
        k++;
    }
    cout << -1 << '\n';
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