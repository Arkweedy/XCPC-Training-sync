#include<bits/stdc++.h>
using ll = long long;
using namespace std;

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }

    int ans = 0;
    while(a.size() > 1){
        vector<int>na;
        for(int i = 0;i < a.size();i++){
            if(i > 0 && a[i] < a[i - 1])continue;
            if(i + 1 < a.size() && a[i] < a[i + 1])continue;
            na.push_back(a[i]);
        }
        ans++;
        a = move(na);
    }
    //if(a.size() == 1)ans++;
    cout<<ans<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while (tt--)
    {
        solve();
    }
    return 0;    
}
