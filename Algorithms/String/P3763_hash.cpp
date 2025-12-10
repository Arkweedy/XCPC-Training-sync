#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    string s,t;
    cin>>s>>t;
    int n = s.length(),m = t.length();
    vector<ull>hs(n),ht(m);
    vector<int>alp(256);
    alp['A'] = 0;
    alp['G'] = 1;
    alp['C'] = 2;
    alp['T'] = 3;
    vector<ull>basepow(max(n,m));
    for(int i = 0;i < n;i++){
        if(i > 0)hs[i] = hs[i - 1];
        hs[i] *= 5;
        hs[i] += alp[s[i]];
    }
    for(int i = 0;i < m;i++){
        if(i > 0)ht[i] = ht[i - 1];
        ht[i] *= 5;
        ht[i] += alp[t[i]];
    }
    basepow[0] = 1;
    for(int i = 1;i < max(n,m);i++){
        basepow[i] = basepow[i - 1] * 5;
    }
    auto get_hash = [&](vector<ull>&hs, int l, int r)->ull
    {
        return hs[r] - (l > 0 ? hs[l - 1] : 0) * basepow[r - l + 1];
    };

    auto find_dif = [&](int sp, int tp)->int // offset
    {
        int l = -1, r = min(n - sp, m - tp);//l ok
        while(r - l > 1){
            int m = l + r >> 1;
            if(get_hash(hs,sp,sp + m) == get_hash(ht,tp,tp + m)){
                l = m;
            }else{
                r = m;
            }
        }
        return r;
    };
    
    int ans = 0;

    for(int i = 0;i < n - m + 1;i++){
        int sp = i, tp = 0;
        int offset = -1;
        int times = 0;
        while(offset < m && times < 4){
            auto res = find_dif(sp,tp);
            sp += res + 1;
            tp += res + 1;
            offset += res + 1;
            times++;
        }
        if(offset == m){
            ans++;
        }
    }
    cout<<ans<<endl;
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