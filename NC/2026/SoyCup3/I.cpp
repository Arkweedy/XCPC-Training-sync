#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.23 14:20:25

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin >> a[i] >> b[i];
        if(i > 0 && a[i] > b[i])swap(a[i], b[i]);
    }
    int ans1 = 0, ans2 = 0;
    // max ans, a0 min, others max
    i64 mi = a[0];
    if(mi < b[0] + m)ans1++;
    for(int i = 1;i < n;i++){
        if(a[i] > mi)ans1 += 2;
        else if(b[i] > mi){
            if(a[i] + m > mi){
                ans1 += 2;
            }
            else{
                ans1 ++;
            }
        }
        else{
            if(a[i] + b[i] + m > mi * 2){
                ans1 += 2;
            }
            else if(b[i] + m > mi){
                ans1++;
            }
            else{
                //
            }
        }
    }

    // min ans , a0 max, others min
    i64 ma = a[0] + m;
    if(ma < b[0])ans2++;
    for(int i = 1;i < n;i++){
        if(a[i] > ma){
            ans2 += 2;
        }
        else if(b[i] > ma){
            ans2 ++;
        }
        else{
            if(a[i] + b[i] + m <= ma * 2){
                //0
            }
            else{
                ans2++;
            }
        }
    }

    cout << ans2 << " " << ans1 << endl;
    return;
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