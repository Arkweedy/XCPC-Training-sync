#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    int n = 100;
    string s;
    for(int i = 0;i < n;i++){
        s += (char)('a' + g() % 2);
    }
    cerr<<s<<endl;

    vector<ull>hs1(n), b1(n);
    vector<ull>hs2(n), b2(n);
    
    ull base1 = 131, base2 = 13331;
    hs1[0] = s[0];
    b1[0] = 1;
    hs2[0] = s[0];
    b2[0] = 1;
    for(int i = 1;i < n;i++){
        hs1[i] = hs1[i - 1] * base1;
        b1[i] = b1[i - 1] * base1;
        hs1[i] += s[i];
        hs2[i] = hs2[i - 1] * base2;
        b2[i] = b2[i - 1] * base2;
        hs2[i] += s[i];
    }

    

    auto get = [&](int l, int r)->pair<ull,ull>
    {
        return make_pair(hs1[r] - (l > 0 ? hs1[l - 1] * b1[r - l + 1] : 0), hs2[r] - (l > 0 ? hs2[l - 1] * b2[r - l + 1] : 0));
    };

    auto lcp = [&](int x, int y)->int //return len(lcp(x, y))
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
    };

    auto lcs = [&](int x, int y)->int //return len(lcs(x, y))
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
    };

    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            for(int k = 1;k + j < n;k++){
                if(s.substr(i,k) == s.substr(j,k)){
                    assert(get(i,i+k-1) == get(j,j + k - 1));
                }
            }
        }
    }
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