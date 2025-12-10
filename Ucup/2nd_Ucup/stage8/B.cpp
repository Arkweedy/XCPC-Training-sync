#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;

void solve()
{
    int n,m;cin>>n>>m;
    vector<int>a(n),b(m);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<m;i++){
        cin>>b[i];
    }
    sort(a.begin(),a.end(),greater<int>());
    sort(b.begin(),b.end(),greater<int>());
    ll sum = 0;
    for(int i=0;i<m;i++){
        if(a[i] > b[i]){
            cout<<"-1"<<'\n';
            return;
        }
        sum += b[i] - a[i];
    }
    if(sum > n - m){
        cout<<-1<<'\n';
        return;
    }
    multiset<int>s,t;
    for(int i=0;i<n;i++){
        s.insert(a[i]);
    }
    for(int i=0;i<m;i++)t.insert(b[i]);
    int cur = n - m - sum;
    vector<int>res;
    for(int i=0;i<cur;i++){
        auto j = (*s.begin());
        res.push_back(j);
        s.erase(s.begin());
        s.insert(j+1);
        last = max(last,(*s.rbegin()));
        s.erase(s.begin());
    }

    

    cout<<res.size()<<'\n';
    for(auto k:res)cout<<k<<' ';
    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
