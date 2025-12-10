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
    vector<int>a1(n),a2(n),b1(n),b2(n);
    int suma = 0, sumb = 0;
    for(int i = 0;i < n;i++){
        cin>>a1[i];
        suma += a1[i];
    }
    for(int i = 0;i < n;i++){
        cin>>a2[i];
        suma += a2[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b1[i];
        sumb += b1[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b2[i];
        sumb += b2[i];
    }
    // for(int i = 1;i < n;i++){
    //     a1[i] += a1[i - 1];
    //     a2[i] += a2[i - 1];
    //     b1[i] += b1[i - 1];
    //     b2[i] += b2[i - 1];
    // }
    if(suma != sumb){
        cout<<-1<<endl;
        return;
    }

    vector<int>d1(n),d2(n);
    for(int i = 0;i < n;i++){
        d1[i] = a1[i] - b1[i];
        d2[i] = a2[i] - b2[i];
    }
    ll ans = 0;
    int pre1 = 0,pre2 = 0;
    for(int i = 0;i < n;i++){
        pre1 += d1[i];
        pre2 += d2[i];
        while(pre1 < 0 && pre2 > 0){
            pre1++;
            pre2--;
            ans++;
        }
        while(pre1 > 0 && pre2 < 0){
            pre1--;
            pre2++;
            ans++;
        }
        ans += abs(pre1) + abs(pre2);
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