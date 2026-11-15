#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;
ll a[7],k;
vector<ll > b;
ll sum=0;
vector<ll> ans;
void dfs(int p){
    if(p==7){
        
        int cnt=0;
        for(auto bb:b)
            for(int i=0;i<6;i++) cnt+=(bb>a[i]);
        //cout<<cnt<<endl;
        if(cnt>=19&&sum<=k){
            ans=b;
            ans[0]+=k-sum;
        }
        return;
    }
    for(int i=0;i<7;i++){
        int g=a[i]+1;
        b.push_back(g);
        sum+=g;
        dfs(p+1);
        sum-=g;
        b.pop_back();
    }

}
void solve()
{
    for(int i=0;i<6;i++) cin>>a[i];
    cin>>k;
    sort(a,a+6);
    dfs(1);

    if(ans.size()){
        cout<<"YES\n";
        for(auto p:ans)  cout<<p<<' ';
        return ;
    }
    cout<<"NO\n";
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

