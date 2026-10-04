#include<bits/stdc++.h>

using ll = long long;
using namespace std;

void solve()
{
    int n;
    cin>>n;
    vector<int>f(n + 1);
    vector<int>fa(n + 2);
    vector<int>iskey(n + 2);//1 -> key path
    vector<int>sz(n + 2);
    vector<vector<int>>ff(n + 2,vector<int>(21));
    //add 
    iskey[0] = 1;
    iskey[1] = 1;
    int key = 1;
    int ans = 0;
    for(int i = 1;i <= n;i++){
        cin>>f[i];//node i + 1 's fa
        fa[i + 1] = f[i];
        ff[i + 1][0] = f[i];
        for(int j = 1;j <= 20;j++){
            ff[i + 1][j] = ff[ff[i + 1][j - 1]][j - 1];
        }
    }
    for(int i = 1;i <= n;i++){
        if(iskey[f[i]]){
            int p = key;
            int sumsz = 0;
            while(p != f[i]){
                iskey[p] = 0;
                sumsz += sz[p] + 1;//add self
                p = fa[p];
                //ans++;
            }
            sz[f[i]] += sumsz;
            ans = max(ans,sz[f[i]]);
            iskey[i + 1] = 1;
            key = i + 1;
        }
        else{
            //jump up
            int p = i + 1;
            for(int j = 20;j >= 0;j--){
                if(!iskey[ff[p][j]]){
                    p = ff[p][j];
                }
            }
            //cerr<<iskey[fa[p]]<<" "<<fa[p]<<endl;
            
            sz[fa[p]]++;
            ans = max(ans, sz[fa[p]]);
        }
        cout<<ans<<"\n";
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
