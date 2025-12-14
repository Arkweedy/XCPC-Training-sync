#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 5e5 + 10;

ll c[N],S,a[N],n;

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    priority_queue<pair<ll,ll>>heap;

    for(int i=1;i<=n;i++)heap.push({a[i],i});

    while(!heap.empty()){
        auto [_,u] = heap.top();
        heap.pop();
        if(a[u] +  S - c[u] * n < n - 1)break;
        S++,c[u]++;
        heap.push({a[u] - c[u] * n, u});

        if(S == n)break;
    }

    if(S == n){
        cout<<"Recurrent\n";
    }else{
        for(int i=1;i<=n;i++)cout<<a[i] + S - c[i] * n <<" \n"[i==n];
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
