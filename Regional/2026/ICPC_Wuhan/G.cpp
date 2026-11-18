#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

void solve()
{
    int n;
    i64 k;
    cin >> n >> k;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());

    int z = 0;
    for(int i = 0;i < n;i++){
        if(a[i] == 0)z++;
    }
    if(z > k){
        cout << n - z + k << endl;
        return;
    }

    for(int i = 0;i < n;i++){
        if(a[i] > 0)a[i]--;
        else k--;
    }

    auto check = [&](i64 x)->int
    {
        x -= n;
        i64 t = x / (n - 1);
        i64 s = x % (n - 1);

        i64 t2 = 0;
        for(int i = 0;i < n;i++){
            t2 += min(max(0ll, t - a[i]), (t + 1) / 2);
        }
        t2 = min(t2, t);
        //cerr << t2 << endl;
        i64 need = 0;
        i64 g = 0;
        for(int i = 0;i < n;i++){
            if(a[i] < t)need += t - a[i];
            if(a[i] > t)g++;
        }
        if(t2 + k < need)return false;

        i64 r = t - t2;
        i64 y = t2 + k - need;
        if(r + y + g >= s)return true;
        else return false;
    };

    //check(9);

    i64 l = n, r = 1e18;
    while(r - l > 1){
        i64 m = (l + r) / 2;
        if(check(m)){
            l = m;
        }
        else{
            r = m;
        }
    }
    cout << l << endl;
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