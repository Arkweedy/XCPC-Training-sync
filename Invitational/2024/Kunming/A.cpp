#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.02 15:25:34

void solve()
{
    int n, m, k;
    cin>>n>>m>>k;
    vector<vector<int>>a(n,vector<int>(m));
    vector<int>s(n);
    vector<ll>sum(n);
    vector<int>free(n);
    for(int i = 0;i < n;i++){
        cin>>s[i];
        for(int j = 0;j < m;j++){
            cin>>a[i][j];
            if(a[i][j] == -1)free[i]++;
            else sum[i] += a[i][j];
        }
    }

    vector<int>id(n);
    iota(id.begin(),id.end(),0);
    sort(id.begin(),id.end(),[&](int i , int j)->bool
    {
        return s[i] == s[j] ? sum[i] < sum[j] : s[i] < s[j];        
    });

    ll l = -1;
    int ls = 0;
    vector<ll>val(n);
    for(int i = 0;i < n;i++){
        int p = id[i];
        if(ls != s[p])l++;
        if(l > sum[p] + 1ll * free[p] * k){
            cout<<"No"<<endl;
            return;
        }
        else{
            val[p] = max(0ll, l - sum[p]);
            l = max(l, sum[p]);
            ls = s[p];
        }
    }

    cout<<"Yes"<<endl;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(a[i][j] == -1){
                if(val[i] >= k){
                    a[i][j] = k;
                    val[i] -= k;
                }
                else{
                    a[i][j] = val[i];
                    val[i] = 0;
                }
            }
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    return;
    
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}