#include<bits/stdc++.h>
using ll = long long;
using i64 = long long;

using namespace std;

int power(int a, i64 p, int m)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % m;
        a = 1ll * a * a % m;
        p >>= 1;
    }
    return res;
}

void solve()
{
    i64 n, m, p;
    cin >> n >> m >> p;
    vector<i64>a(m);
    for(int i = 0;i < m;i++){
        cin >> a[i];
    }
    a.push_back(1);
    a.push_back(0);
    m += 2;
    sort(a.begin(),a.end());
    i64 cnt = n - a.back();
    i64 T = a.back();
    int isPal = 1;
    for(int i = m - 1;i >= 1;i--){
        i64 x = T - a[i], y = T - a[i - 1];
        if(x <= 0 || y <= 0)continue;
        //cerr << T << " " << x << " " << y << endl;
        i64 gT = gcd(x, y);
        if(x + y - gT <= T){
            T = gT;
            isPal = 0;
        }
        else{
            i64 nT = max(a[i], a[i - 1]);
            if(isPal){
                //cerr << "#ele : " << nT + 1 << " ~ " <<  (T + 1) / 2 << endl;
                cnt += max(0ll, (T + 1) / 2 - nT);
            }
            else{
                //cerr << "&ele : " << nT + 1 << " ~ " << T << endl;
                cnt += T - nT;
            }
            isPal = 1;
            T = nT;
        }
    }
    cnt++;//1
    //cerr << "#" << cnt << endl;
    int ans = power(2, cnt, p);
    //cerr << "scc = " << cnt << endl;
    cout << ans << endl;
    return;
    //22
}   

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}