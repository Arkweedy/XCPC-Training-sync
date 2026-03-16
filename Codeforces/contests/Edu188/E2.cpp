#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.17 00:16:56

int digit(int n)
{
    int res = 0;
    while(n){
        res += n % 10;
        n /= 10;
    }
    return res;
}

constexpr int N = 1e6;
vector<vector<int>>g(N + 1);

void init()
{
    for(int i = 10;i <= N;i++){
        g[digit(i)].push_back(i);
    }
}

void solve()
{
    string s;
    cin >> s;

    if(s.length() == 1){
        cout << s << endl;
        return;
    }

    vector<int>c(10);
    int n = s.length();
    for(int i = 0;i < n;i++){
        c[s[i] - '0']++;
    }

    int sum = 0;
    for(int i = 0;i < 10;i++){
        sum += c[i] * i;
    }

    int vsum = sum;
    auto v = c;

    auto add = [&](int x, int y)->void
    {
        while(x){
            vsum += x % 10 * y;
            v[x % 10] += y;
            x /= 10;
        }
        return;
    };

    auto ok = [&](int x)->bool
    {
        if(vsum < x)return false;
        for(int i = 0;i < 10;i++){
            if(v[i] < 0)return false;
        }
        return true;
    };

    auto ok2 = [&](int x)->bool
    {
        int rem = 0;
        for(int i = 0;i < 10;i++){
            rem += v[i] * i;
        }
        return rem == x;
    };

    string ans;
    auto dfs = [&](auto&&self, int p)->bool
    {
        if(!ok(p))return false;
        if(ok2(p)){
            for(int i = 9;i >= 0;i--){
                ans += string(v[i], char(i + '0'));
            }
            ans += to_string(p);
            return true;
        }
        for(auto s : g[p]){
            add(s, -1);
            if(vsum < s){
                add(s, 1);
                break;
            }
            int okk = self(self, s);
            add(s, 1);
            if(okk){
                ans += to_string(p);
                return true;
            }
        }
        return false;
    };

    for(int i = 1;i < 10;i++){
        add(i, -1);
        if(dfs(dfs, i)){
            cout << ans << "\n";
            return;
        }
        add(i, 1);
    }
    return;

}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    init();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}