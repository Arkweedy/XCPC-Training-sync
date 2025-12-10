#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int a[100005]{};

void solve()
{
    int n,m;
    cin>>n>>m;
    vector<int>p(m);
    vector<int>time;
    for(int i = 0;i < m;i++){
        cin>>p[i];
        a[p[i]]++;
        if(a[p[i]] == 1)time.push_back(p[i]);
    }
    vector<int>rk = time;
    sort(rk.begin(),rk.end(),[&](int i, int j)->bool
    {
        return a[i] == a[j] ? i < j : a[i] > a[j];
    });

    int ans = 0;
    for(int i = 0;i < time.size();i++){
        if(time[i] != rk[i]){
            ans++;
        }
    }
    cout<<ans<<"\n";
    for(int i = 0;i < m;i++){
        a[p[i]]--;
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