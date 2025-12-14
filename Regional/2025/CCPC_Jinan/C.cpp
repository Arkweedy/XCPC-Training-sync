#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

void solve()
{
    int m;cin>>m;
    vector<int>p(m),q(m);
    for(int i=0;i<m;i++){
        cin>>p[i];p[i]--;
        q[p[i]] = i;
    }

    int n;cin>>n;
    while(n--){
        vector<int>cnt(m+1);
        int l;cin>>l;
        cnt[0] = l;
        while(l--){
            int x;cin>>x;
            if(x > m)continue;
            x--;
            x = q[x];
            if(cnt[x]){
                cnt[x]--;
                cnt[x+1]++;
            }
        }

        cout<<cnt[m]<<'\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}
