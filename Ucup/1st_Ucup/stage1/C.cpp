#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.23 16:49:13

void solve()
{
    int n, d;
    cin >> n >> d;
    vector<int>a(n);
    for(int i = 0;i < n; i++){
        cin >> a[i];
    }
    vector<int>sa = a;
    sort(sa.begin(), sa.end());
    sa.erase(unique(sa.begin(), sa.end()), sa.end());
    for(int i = 0;i < n;i++){
        a[i] = lower_bound(sa.begin(), sa.end(), a[i]) - sa.begin();
    }
    int m = sa.size();
    vector<int>c(m);
    for(int i = 0;i < n - 1;i++){
        if(a[i] < a[i + 1]){
            c[a[i]]--;
            c[a[i + 1]]++;
        }
        else{
            c[a[i]]++;
            c[a[i + 1]]--;
        }
    }


    int v = sa[0] - d, l = 0, r = 1; //pointer to next
    // v -> left value
    int ldelta = 0, rdelta = 0;
    for(int i = 1;i < m;i++){
        rdelta += c[i];
    }
    i64 ans = 0;
    i64 res = 0;
    while(l < m){
        cerr << l << " " << r << endl;
        int nv = min(sa[l], sa[r] - d);
        if(r == m){
            ldelta += c[l++];
        }
        else if(sa[r] < sa[l] + d){//update rd
            rdelta -= c[r++];
        }
        else if(sa[r] > sa[l] + d){//update ld
            ldelta += c[l++];
        }
        else{
            ldelta += c[l++];
            rdelta -= c[r++];
        }
        res += 1ll * (ldelta - rdelta) * (nv - v);
        ans = max(ans, res);
    }
    cout << ans << endl;
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