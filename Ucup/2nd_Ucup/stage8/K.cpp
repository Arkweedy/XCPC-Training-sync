#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 200;
int n,m;
vector<int> a[N];
vector<int> operator *(vector<int> a,vector<int> b)
{
    vector<int> c(m+1);
    c[0]=0;
    for(int i=1;i<=m;i++) c[i]=a[b[i]];
    return c;
}
map<vector<int> ,int> mp;
int dp[100][400009];
vector<int> pre[400009];
int pm;
void solve()
{
    cin>>m>>n;
    if(n==1||m==1)
    {
        cout<<1;
        return ;
    }
    for(int i=0;i<n;i++)
        {
         a[i].resize(m+1);
         for(int j=1;j<=m;j++) cin>>a[i][j];
}
    if(m<=9)
    {
        pm=1;
        for(int i=1;i<=m;i++) pm*=i;
        vector<int> ve(m+1);
        for(int i=0;i<=m;i++) ve[i]=i;
        int cnt=0;
        do
        {
            mp[ve]=cnt;
            pre[cnt]=ve;
            cnt++;
        }while(next_permutation(ve.begin()+1,ve.end()));
        dp[0][mp[a[0]]]=1;
        for(int i=0;i<n-1;i++)
        {
            dp[i+1][mp[a[i+1]]]=1;
            for(int j=0;j<pm;j++)
                if(dp[i][j])
                {
                    dp[i+1][j]=1;
                    auto c=pre[j]*a[i+1];
                    dp[i+1][mp[c]]=1;
                }
}
        int ans=0;
        for(int i=0;i<pm;i++) ans+=dp[n-1][i];
        cout<<ans;
    }
    else
    {
        int ans=0;
        for(int i=1;i<(1<<n);i++)
        {
           // cout<<i<<endl;
            vector<int> ve(m+1);
            for(int i=0;i<=m;i++) ve[i]=i;
            for(int j=0;j<n;j++)
                if(i>>j&1)
                {
                    ve=ve*a[j];
                }
            if(!mp[ve]) mp[ve]=1,ans++;
        }
        cout<<ans;
    }
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
