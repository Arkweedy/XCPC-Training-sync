#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


//Create time: 2025.11.06 13:59:22

struct Hash
{
    static constexpr int P1 = 1000000007;
    static constexpr int P2 = 1000000009;

    static constexpr int b1 = 131;
    static constexpr int b2 = 13331;

    int n;
    vector<int>h1,p1,h2,p2;
public:

    Hash(vector<int>& s)//default 
    {
        n = s.size();
        h1.resize(n);
        p1.resize(n);
        h2.resize(n);
        p2.resize(n);

        p1[0] = 1;
        h1[0] = s[0];
        p2[0] = 1;            
        h2[0] = s[0];
        for (int i = 1; i < n; ++i) {
            p1[i] = 1ll * p1[i-1] * b1 % P1;
            p2[i] = 1ll * p2[i-1] * b2 % P2;
            h1[i] = (1ll * h1[i-1] * b1 + s[i]) % P1;
            h2[i] = (1ll * h2[i-1] * b2 + s[i]) % P2;
        }
    }

    pair<int,int> get(int l, int r)
    {
        int hs1 = h1[r], hs2 = h2[r];
        if(l)hs1 -=  1ll * h1[l - 1] * p1[r - l + 1] % P1, hs2 -= 1ll * h2[l - 1] * p2[r - l + 1] % P2;
        if(hs1 < 0)hs1 += P1;
        if(hs2 < 0)hs2 += P2;
        return make_pair(hs1,hs2);
    }

    int lcp(int x, int y)
    {
        int l = 0, r = min(n - x, n - y) + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            if(get(x, x + m - 1) == get(y, y + m - 1)){
                l = m;
            }
            else{
                r = m;
            }
        }
        return l;
    }

    int lcs(int x, int y)
    {
        int l = 0, r = min(x + 1, y + 1) + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            if(get(x - m + 1, x) == get(y - m + 1, y)){
                l = m;
            }
            else{
                r = m;
            }
        }
        return l;
    }
};

vector<int> z_function(vector<int> s) {
  int n = (int)s.size();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r && z[i - l] < r - i + 1) {
      z[i] = z[i - l];
    } else {
      z[i] = max(0, r - i + 1);
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    }
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>s(n);
    for(int i = 0;i < n;i++){
        cin >> s[i];
    }
    Hash hs(s);
    auto z = z_function(s);
    ll sum = 0;
    for(int i = 0;i < n;i++){
        sum += z[i];//z[0] = 0;
    }
    sum += n;
    vector<ll>a(n + 1, sum);
    vector<ll>d(n + 1), dd(n + 1);
    vector<map<int,ll>>mp(n + 1);

    auto calc = [&]()->void
    {
        vector<ll>da(n);//no ll see zuzong
        vector<ll>aa(n);
        da[0] = dd[0];
        for(int i = 1;i < n;i++){
            da[i] = da[i - 1] + dd[i];
        }
        aa[0] = d[0] + da[0];
        for(int i = 1;i < n;i++){
            aa[i] = aa[i - 1] + d[i] + da[i];
        }
        for(int i = 0;i < n;i++){
            a[i] += aa[i];
        }

        for(int i = 0;i < n;i++){
            ll v = 0;
            for(auto [c,x] : mp[i]){
                v = max(v, x);
            }
            a[i] += v;
        }
        return;
    };

    auto dec = [&](int l, int r, int val)->void
    {
        //cerr<<"dec ["<<l<<","<<r<<"] "<<val<<endl;
        d[l] -= val + 1;
        d[r + 1] += val + 1;
        dd[l] += 1;
        dd[r + 1] -= 1;
        d[r + 1] -= (r - l + 1);
    };

    auto add = [&](int p, int val, int ch)->void
    {
        //cerr<<"add "<<p<<" "<<val<<endl;
        mp[p][ch] += val;
    };

    auto get = [&](int x, int y, int op, int ch)->int //len
    {
        int l = 0, r = min(n - x, n - y) + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            auto hx = hs.get(x, x + m - 1), hy = hs.get(y, y + m - 1);
            if(op == 0){//modify x
                auto [x1,x2] = hx;
                x1 = (x1 - 1ll * s[x] * hs.p1[m - 1] + 1ll * ch * hs.p1[m - 1]) % hs.P1;
                x2 = (x2 - 1ll * s[x] * hs.p2[m - 1] + 1ll * ch * hs.p2[m - 1]) % hs.P2;
                if(x1 < 0)x1 += hs.P1;
                if(x2 < 0)x2 += hs.P2;
                hx = {x1,x2};
            }
            else{//modify y
                auto [y1,y2] = hy;
                y1 = (y1 - 1ll * s[y] * hs.p1[m - 1] + 1ll * ch * hs.p1[m - 1]) % hs.P1;
                y2 = (y2 - 1ll * s[y] * hs.p2[m - 1] + 1ll * ch * hs.p2[m - 1]) % hs.P2;
                if(y1 < 0)y1 += hs.P1;
                if(y2 < 0)y2 += hs.P2;
                hy = {y1,y2};
                if(x + m - 1 >= y){
                    auto [x1,x2] = hs.get(x, y - 1);
                    x1 = (1ll * x1 * hs.b1 + ch) % hs.P1;
                    x2 = (1ll * x2 * hs.b2 + ch) % hs.P2;
                    if(x1 < 0)x1 += hs.P1;
                    if(x2 < 0)x2 += hs.P2;
                    int len = x + m - 1 - y;
                    auto [t1,t2] = hs.get(y + 1, x + m - 1);
                    x1 = (1ll * x1 * hs.p1[len] + t1) % hs.P1;
                    x2 = (1ll * x2 * hs.p2[len] + t2) % hs.P2;
                    hx = {x1,x2};
                }
            }    
            if(hx == hy){
                l = m;
            }
            else{
                r = m;
            }
        }
        return l;
    };

    for(int i = 1;i < n;i++){
        if(z[i] <= i){
            dec(0, z[i] - 1, z[i]);
            dec(i, i + z[i] - 1, z[i]);
            if(i + z[i] < n){
                if(z[i] < i)add(z[i], get(z[i], i + z[i], 0, s[i + z[i]]), s[i + z[i]]);
                add(i + z[i], get(z[i], i + z[i], 1, s[z[i]]),s[z[i]]);
            }
        }
        else{
            dec(0, i - 1, z[i]);
            dec(i, i + z[i] - 1, z[i]);
            if(i + z[i] < n)add(i + z[i], get(z[i], i + z[i], 1, s[z[i]]),s[z[i]]);
        }
    }

    calc();

    ll ans = 0;
    for(int i = 0;i < n;i++){
        ans += (a[i] ^ (i + 1));
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