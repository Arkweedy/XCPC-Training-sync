#include<bits/stdc++.h>

using i64 = long long;

using namespace std;

void solve()
{
    int n, k;
    i64 s;
    cin >> n >> k >> s;
    vector<pair<i64, i64>>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(),a.end());
    for(int i = 0;i < n;i++){
        while(k > 0 && s < a[i].first){
            s *= 2;
            k--;
        }
        if(s >= a[i].first){
            s += a[i].second;
        }
        else{
            break;
        }
    }
     while(k > 0){
        s *= 2;
        k--;
    }
    cout << s << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}