#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

i64 n, m;
i64 ans2;
vector<i64>a;
i64 res;

void solve1()
{
    cin >> n >> m;
    ans2 = m;
    a.resize(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<pair<int,int>>ans;
    i64 p = n;

    
    //cerr << m << endl;
    
    while(m != 0 && p * (n - p + 1) <= m){
        for(int i = 0;i + p <= n;i++){
            ans.emplace_back(i + 1, i + p);
        }
        m -= p * (n - p + 1);
        p--;
    }


    if(p == 0){
        for(auto [l, r] : ans){
            cout << l << " " << r << endl;
        }
        return;
    }

    //cerr << m << ' ' << p << endl;

    //
    i64 s = m / p, t = m % p;
    vector<i64>c;
    i64 sum = 0;
    for(int i = 0;i < p - 1;i++){
        sum += a[i];
    }
    for(int i = p - 1;i < n;i++){
        sum += a[i];
        c.push_back(sum);
        sum -= a[i - p + 1];
    }

    vector<int>id(n - p + 1);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int i, int j)->bool
    {
        return c[i] > c[j];
    });
    for(int i = 0;i < s;i++){
        ans.emplace_back(id[i] + 1, id[i] + p);
    }

    vector<int>aid(n);
    iota(aid.begin(), aid.end(), 0);
    sort(aid.begin(), aid.end(), [&](int i, int j)->bool
    {
        return a[i] < a[j];
    });
    for(int i = 0;i < t;i++){
        ans.emplace_back(aid[i] + 1, aid[i] + 1);
    }

    for(auto [l, r] : ans){
        for(int i = l;i <= r;i++){
            res += a[i - 1];
        }
    }

    cerr << "%" << res << endl;

    for(auto [l, r] : ans){
        cout << l << " " << r << endl;
    }
    return;
}

void solve2()
{
    //i64 n, x;
    //cin >> n >> x;
    i64 x;
    x = res;

    cerr << n << " " << x << endl;
    
    // vector<i64>a(n);
    i64 sum = 0;
    for(int i = 0;i < n;i++){
        //cin >> a[i];
        sum += a[i];
    }
    vector<i64>p(n),s(n),pp(n),ss(n);
    for(int i = 0;i < n;i++){
        p[i] = a[i];
        if(i > 0)p[i] += p[i - 1];
        pp[i] = p[i];
        if(i > 0)pp[i] += pp[i - 1];
    }
    for(int i = n - 1;i >= 0;i--){
        s[i] = a[i];
        if(i + 1 < n)s[i] += s[i + 1];
        ss[i] = s[i];
        if(i + 1 < n)ss[i] += ss[i + 1];
    }

    auto get = [&](int k)->i64
    {
        if(k == n)return sum;
        else return sum * (n - k + 1) - pp[n - k - 1] - ss[k];
    };

    i64 q = n;
    i64 ans = 0;
    while(x != 0 && get(q) <= x){
        x -= get(q);
        ans += q * (n - q + 1);
        q--;
    }

    cerr << "&&&" << ans << " " << x << endl;

    cerr << sum << endl;

    if(x == 0){
        cout << ans <<endl;
        return;
    }

    //cerr << q << " " << x << " " << ans << endl;


    vector<i64>c;
    i64 sum2 = 0;
    for(int i = 0;i < q - 1;i++){
        sum2 += a[i];
    }
    for(int i = q - 1;i < n;i++){
        sum2 += a[i];
        c.push_back(sum2);
        sum2 -= a[i - q + 1];
    }

    vector<int>id(n - q + 1);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int i, int j)->bool
    {
        return c[i] > c[j];
    });

    for(int i = 0;i < n - q + 1;i++){
        if(x >= c[id[i]]){
            x -= c[id[i]];
            ans += q;
        }
        else break;
    }

    vector<int>aid(n);
    iota(aid.begin(), aid.end(), 0);
    sort(aid.begin(), aid.end(), [&](int i, int j)->bool
    {
        return a[i] < a[j];
    });

    for(int i = 0;i < n;i++){
        if(x >= a[aid[i]]){
            x -= a[aid[i]];
            ans++;
        }
        else{
            break;
        }
    }

    cout << ans << endl;
    assert(ans == ans2);
    assert(x == 0);
    cerr << "OK" << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve1();
        solve2();
    }
    return 0;
}