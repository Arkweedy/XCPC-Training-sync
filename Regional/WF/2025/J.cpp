#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.25 15:21:25

bool check(ll n,ll h){
    if(h == 0)return 1;
    if(n == 0)return 0;
    if(n == 1)return h == 1;
    return h != 2 && h != n * n - 2 && h > 0 && h <= n * n;
}

void solve()
{
    ll n,h;cin>>n>>h;
    
    if(h < 2 * n -1 || h > n * n){
        cout<<"impossible\n";
        return;
    }
    vector<int>a,b;
    int m = n;
    for(ll i=2*n-1;i>0 && h > 0;i-=2){
        if(check(m-1,h-i)){
            b.push_back(i);
            h -= i;
            m--;
            break;
        }
        a.push_back(i);
        m--,h--;
    }
    if(b.empty()){
        cout<<"impossible\n";
        return;
    }
    
    int t = b.back();
    vector<int>c;

    while(t > 1){
        t -= 2;
        if(check(m-1,h-t) && h >= t){
            b.push_back(t);
            h -= t;
        }else{
            c.push_back(t);
        }
    }

    a.insert(a.end(),b.rbegin(),b.rend());
    a.insert(a.end(),c.begin(),c.end());

    for(auto k:a)cout<<k<<' ';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}