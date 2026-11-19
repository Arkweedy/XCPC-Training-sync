#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

const int N = 101;
vector<int> v;
int k;
int dp[N][N];
int f(int x,int y)
{
    if(y <= k) return 1;
    if(dp[x][y] != -1) return dp[x][y];
    dp[x][y]  = 0;
    if(v[x] == v[x + 1])
    {
        for(int i = 1;i <= k;i++)
        {
            dp[x][y] = max(dp[x][y],f(x+1,y-i));
        }
    }
    else
    {
        for(int i = 1;i <= k;i++)
        {
            dp[x][y] = max(dp[x][y],1 ^ f(x + 1,y-i));
        }
    }
    return dp[x][y];
}
void solve(int pp)
{
    k = pp;
    for(int i = 0;i < N;i++)
    {
        for(int j  = 0;j < N;j++)
        {
            dp[i][j] = -1;
        }
    }
    cout << k << '\n';
    for(int i = 1;i < N;i++)
    {
        cout << f(0,i) << ' ';

    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    v.push_back(0);
    for(int i = 0;i <= 10;i++)
    {
        vector<int> temp = v;
        for(int j = 0;j < temp.size();j++)
        {
            temp[j] = 1 ^ temp[j];
            v.push_back(temp[j]);
        }
    }

    for(int i = 1;i < N;i++)
    {
        solve(i);
    }
    return 0;
}