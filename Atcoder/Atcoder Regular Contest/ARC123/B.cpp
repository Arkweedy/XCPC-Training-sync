#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.30 10:38:43

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n),b(n),c(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
    }
    for(int i = 0;i < n;i++){
        cin>>c[i];
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());

    auto check = [&](int m)->bool
    {
        //int l = a[0], r = c[n - m];
        int p = lower_bound(b.begin(),b.end(),a[0]) - b.begin();
        for(int i = 0;i < m;i++){
            while(p < n && b[p] <= a[i])p++;
            if(p < n && b[p] < c[n - m + i])p++;
            else return false;            
            // if(a[i] + 1 >= c[n - m + i]){
            //     return false;
            // }
            // if(a[i] > r){
            //     l = a[i], r = c[n - m + i], p = i;
            // }
            // else{
            //     r = c[n - m + i];
            // }
            // int c = upper_bound(b.begin(),b.end(),r - 1) - lower_bound(b.begin(),b.end(),l + 1);
            // if(c < i - p + 1){
            //     return false;
            // }
        }
        return true;
    };

    int l = 0, r = n + 1;
    while(r - l > 1){
        int m = l + r >> 1;
        if(check(m)){
            l = m;
        }
        else{
            r = m;
        }
    }
    cout<<l<<endl;
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