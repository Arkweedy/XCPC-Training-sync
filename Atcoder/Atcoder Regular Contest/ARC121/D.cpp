#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    int l = 0, r = 0;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
        if(a[i] >= 0)r++;
        else l++;
    }
    if(l > r){
        for(int i = 0;i < n;i++){
            a[i] = -a[i];
        }
        swap(l,r);
    }
    
    sort(a.begin(),a.end());

    constexpr int inf = 2e9;
    int L = inf,R = -inf;
    for(int i = 0;i < l;i++){
        int x = a[i] + a[n - i - 1];
        L = min(L, x);
        R = max(R, x);
    }

    

    int ans = inf;
    for(int i = 0;i <= r - l; i += 2){
        int iL = L, iR = R;
        for(int j = 0;j < i;j++){
            int x = a[l + j] + a[l + i - j - 1];
            iL = min(iL, x);
            iR = max(iR, x);
        }
        for(int j = l + i;j < n - l;j++){
            iL = min(iL, a[j]);
            iR = max(iR, a[j]);
        }
        ans = min(ans, iR - iL);
    }

    cout<<ans<<endl;
    return;
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