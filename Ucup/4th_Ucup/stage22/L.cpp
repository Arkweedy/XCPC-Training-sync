#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;
using i128 = __int128;

using namespace std;

void write(i128 x)
{
    if(x == 0)return;
    if(x<0)cout<<'-',x = -x;
    write(x/10);
    cout<<(int)(x%10);
}

constexpr int P = 998244353;

void solve()
{ 
    int n;
    cin>> n;
    string s;
    cin >> s;
    s = 'a' + s;
    set<int>a, b, c, d;
    for(int i = i;i <= n;i++){
        if(s[i] == 'K'){
            a.insert(i);
        }
        else if(s[i] == 'U'){
            b.insert(i);
        }
        else if(s[i] == 'P'){
            c.insert(i);
        }
        else if(s[i] == 'C'){
            d.insert(i);
        }
    }

    // cerr << s << endl;
    // cerr << a.size() << " " << b.size() << " " << c.size() << " " << d.size() << endl;

    i64 ans = 0;

    for(auto rit = d.rbegin(); rit != d.rend();rit++){
        auto e = *rit;

        if(c.empty())break;
        auto zit = c.upper_bound(e);
        if(zit == c.begin())continue;
        int z = *prev(zit);
        

        if(b.empty())break;
        auto yit = b.upper_bound(z);
        if(yit == b.begin())continue;
        int y = *prev(yit);
        
        

        if(a.empty())break;
        auto xit = a.upper_bound(y);
        if(xit == a.begin())continue;
        int x = *prev(xit);
        a.erase(x);
        b.erase(y);
        c.erase(z);
        

        ans = (ans + 1ll * e * z % P * y % P * x) % P;
    }
   
    cout << ans << endl;
    
    return;
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