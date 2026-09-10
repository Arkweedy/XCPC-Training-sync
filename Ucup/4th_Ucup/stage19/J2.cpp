#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.09.10 20:36:03

void solve()
{
    int n;
    i64 k;
    cin >> n >> k;
    i64 base = 0;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        base += a[i] / k;
        a[i] %= k;
    }
    vector<i64>p(n + 1);
    
    for(int i = 0;i < n;i++){
        if(i % 2 == 0)p[i + 1] = (p[i] + a[i]) % k;
        else p[i + 1] = ((p[i] - a[i]) % k + k) % k;
    }
    auto sp = p;
    sort(sp.begin(),sp.end());
    sp.erase(unique(sp.begin(), sp.end()), sp.end());
    for(int i = 0;i <= n;i++){
        p[i] = lower_bound(sp.begin(),sp.end(), p[i]) - sp.begin();
    }
    int m = p.size();
    int m2 = m * 2;
    vector<i64>d(m * 2 + 1);
    // even : p * 2
    // odd : p * 2 + 1
    auto add = [&](int l, int r)->void
    {
        d[l]++;
        d[r + 1]--;
    };

    d[0]++;
    d[1]--;
    int la = m * 2 - 1;
    for(int i = 0;i < n;i++){
        int bg = p[i], ed = p[i + 1];
        if(bg == ed)continue;
        if(i % 2 == 0){
            int pb = bg * 2 + 1, pe = ed * 2;
            if(pb < pe){
                add(pb, pe);
            }
            else{
                add(pb, la);
                add(0, pe);
            }
        }
        else{
            int pb = (bg * 2 - 1 + m2) % m2, pe = ed * 2;
            if(pb > pe){
                add(pe, pb);
            }
            else{
                add(0, pb);
                add(pe, la);
            }   
        }
    }

    i64 cnt = d[0];
    i64 mi = cnt, ma = cnt;
    for(int i = 1;i < m2;i++){
        cnt += d[i];
        mi = min(mi, cnt);
        ma = max(ma, cnt);
    }
    cout << base + mi << " " << base + ma << endl;
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