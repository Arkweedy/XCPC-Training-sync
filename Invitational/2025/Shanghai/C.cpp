#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;



using namespace std;


void solve()
{
    ll n, m, val, l ,r;
    cin>>n>>m>>val>>l>>r;
    ll sumc = 0;
    vector<ll>s(n),a(n),b(n),c(n);
    for(int i = 0;i < n;i++){
        cin>>s[i]>>a[i]>>b[i]>>c[i];
        sumc += s[i];
    }
    m = min(m ,sumc);
    ll mi = 2e12;
    ll ma = -2e6;
    for(int i = 0;i < n;i++){
        mi = min(mi, a[i] - (s[i] - 1) * b[i]);
        ma = max(ma,a[i] + c[i]);
    }
    cerr<<mi<<" "<<ma<<endl;
    
    auto calc = [&](int p, ll v)->ll
    {
        if(v > a[p] + c[p])return 0;
        else return min(s[p], 1 + max(0ll, (a[p] - v) / b[p]));
    };
    auto calc_all = [&](ll v)->ll
    {
        ll res = 0;
        for(int i = 0;i < n;i++){
            res += calc(i,v);
        }
        return res;
    };

    auto get_val = [&](ll cnt)->ll // find smaller val 
    {
        ll L = mi, R = ma + 1;
        while(R - L > 1){
            ll M = L + R >> 1;
            if(calc_all(M) <= cnt){// val 
                R = M;
            }
            else{
                L = M;
            }
        }
        return R;
    };
    auto calc_sum = [&](int p,  ll v)->ll
    {
        if(v > a[p] + c[p]){
            return 0;
        }
        else{
            ll cnt = calc(p,v);
            return c[p] + cnt * a[p] - (cnt * (cnt - 1)) / 2 * b[p];
        }
    };

    auto calc_allsum = [&](ll v)->ll
    {
        ll sum = 0;
        for(int i = 0;i < n;i++){
            sum += calc_sum(i,v);
        }
        return sum;
    };

    auto get_ans =[&](ll x)->ll
    {
        if(x > m)return -1;
        ll lval = get_val(x);
        ll lcnt = calc_all(lval);
        ll res = calc_allsum(lval) + (x - lcnt) * (lval - 1);
        if(l <= x && x <= r)res += val;
        return res;
    };

    ll zrcnt = calc_all(0);
    ll ans = -1;
    ans = max({get_ans(l),get_ans(r),get_ans(zrcnt),get_ans(min(zrcnt,m))});
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