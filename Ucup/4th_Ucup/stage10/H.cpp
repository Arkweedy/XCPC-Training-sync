#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.02 15:46:15

void solve()
{
    int n;cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    auto b = a;
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    int m = b.size();
    vector<int>cnt(m);
    for(int i=0;i<n;i++){
        a[i] = lower_bound(b.begin(),b.end(),a[i]) - b.begin();
        cnt[a[i]]++;
    }
    int mx = * max_element(cnt.begin(),cnt.end());

    int cost = 2 * n , v = mx;
    for(int i=mx;i<=n;i++){
        int w = i - 1;
        if(b[m-1] == 2 * b[0])w += max(0,cnt[m-1] -1  + cnt[0] - 1 - (i-1));
        if(w < cost)cost = w,v = i;
    }

    vector<vector<int>>e(v);
    for(int i=0;i<cnt[0];i++)e[i].push_back(b[0]);
    if(m > 1)for(int i=0;i<cnt[m-1];i++)e[v-1-i].push_back(b[m-1]);
    
    for(int i=1;i+1<m;i++){
        for(int j=0;j<cnt[i];j++)e[j].push_back(b[i]);
    }

    cout<<cost<<'\n';

    int pre = 0,res = 0;
    for(int i=0;i<v;i++){
        sort(e[i].begin(),e[i].end());
        for(auto x:e[i]){
            res += (pre / x);
            cout<<x<<' ';
            pre = x;
        }
    }
    cout<<'\n';
    //cout<<res<<endl;
    assert(res == cost);

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