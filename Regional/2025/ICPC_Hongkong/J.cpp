#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.29 14:00:08

void solve()
{
    int n;cin>>n;
    vector<ll>l(3);

    vector<int>p(3);
    iota(p.begin(),p.end(),0);

    for(int i=0;i<3;i++)cin>>l[i];
    
    sort(p.begin(),p.end(),[&](int x,int y){
        return l[x] < l[y];
    });

    sort(l.begin(),l.end());
    vector<vector<ll>>e(3);
    ll cur = 0;
    for(int i=0;i<n;i++){

        int q,c;cin>>q>>c;
        q--;

        for(int i=0;i<3;i++){
            if(p[i] == q){
                q = i;
                break;
            }
        }

        e[q].push_back(c);

        cur += c;
    }
    
    ll res = 0;
    ll t;cin>>t;

    if(cur > l[2]){
        cout<<"NO\n";
        return;
    }

    for(int i=0;i<3;i++)l[i] = min(cur,l[i]);

    priority_queue<int>heap;
    
    int idx = 2;
    for(int i=0;i<n;i++){

        while(idx >= 0 && cur <= l[idx]){
            for(auto x:e[idx])heap.push(x);
            idx--;
        }

        while(heap.empty()){
            cur = min(cur,l[idx]);
            for(auto x:e[idx])heap.push(x);
            idx--;
        }

        auto y = heap.top();
        heap.pop();
        res += cur;
        cur -= y;

        if(res >= t || cur < 0){
            cout<<"NO\n";
            return;
        }

    }

    cout<<"YES\n";

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