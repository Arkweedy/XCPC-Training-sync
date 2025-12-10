#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

const int N = 1e6 + 10;

int n,a[N],lp[N],rp[N];
int lc[N],rc[N];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    
    vector<int>stk(1,0);
    // for(int i=1;i<=n;i++){
    //     while(a[stk.back()] > a[i]){
    //         stk.pop_back();
    //     }
    //     lp[i] = stk.back();
    //     stk.push_back(i);
    // }

    for(int i=1;i<=n;i++){
        int p = i-1;
        while(a[p] > a[i]){
            p = lp[p];
        }
        lp[i] = p;
    }
    
    stk.clear();
    stk.push_back(n+1);
    for(int i = n;i;i--){
        while(a[stk.back()] >= a[i]){
            stk.pop_back();
        }
        rp[i] = stk.back();
        stk.push_back(i);
    }
    
   
    for(int i=1;i<=n;i++){
        int p = i - 1;
        while(a[p] && a[p] % a[i]==0){
            p = lc[p];
        }
        lc[i] = p;
    }
    
    
    rc[n+1] = n+1;
    for(int i=n;i;i--){
        int p = i+1;
        while(a[p] && a[p]%a[i]==0){
            p = rc[p];
        }
        rc[i] = p;
    }

    ll res = 0;
    for(int i = 1;i<=n;i++){
    
        int l = max(lp[i],lc[i]);
        int r = min(rp[i],rc[i]);
        
        res += 1ll*(i-l) *(r-i);
    }

    cout<<res;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}