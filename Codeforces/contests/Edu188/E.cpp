#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.16 23:14:33

int digit(int n)
{
    int res = 0;
    while(n){
        res += n % 10;
        n /= 10;
    }
    return res;
}

void solve()
{
    string s;
    cin >> s;
    vector<int>c(10);
    int n = s.length();
    for(int i = 0;i < n;i++){
        c[s[i] - '0']++;
    }

    int sum = 0;
    for(int i = 0;i < 10;i++){
        sum += c[i] * i;
    }

    int len = max((int)ceill(log10l(sum)), 3);
    //cerr << sum << " " << len << endl;
    // sum leq 9e5 (6 digit)
    // digit(sum) leq 53

    vector<vector<int>>f(54, vector<int>(10));
    vector<int>csum(54);
    vector<string>ss(54);
    for(int i = 1;i <= 53;i++){
        if(i < 10){
            f[i][i] = 1;
            ss[i] = to_string(i);
        }
        else{
            string t;
            int x = i;
            while(x >= 10){
                t += to_string(x);
                f[i][x % 10]++;
                f[i][x / 10]++;
                x = digit(x);
            }
            t += to_string(x);
            f[i][x]++;
            ss[i] = t;
        }

        for(int j = 0;j < 10;j++){
            csum[i] += f[i][j] * j;
        }
    }

    auto check = [&](string& t)->bool
    {
        if(t.length() != n)return false;
        vector<int>tc(10);
        for(int i = 0;i < n;i++){
            tc[t[i] - '0']++;
        }
        for(int i = 0;i < 10;i++){
            if(tc[i] != c[i])return false;
        }
        return true;
    };

    string ans;
    auto dfs = [&](auto&&self, int x, int dep)->bool
    {
        //check x'
        if(dep >= len)return false;
        //cerr << "check " << x << endl;
        if(x <= 53){
            //cerr << x << " " << sum << "  " << csum[x] << endl;
            if(csum[x] == sum){
                //
                string t;
                for(int i = 1;i < 10;i++){
                    if(c[i] - f[x][i] < 0)goto out;
                    t += string(c[i] - f[x][i], char(i + '0'));
                }
                if(c[0] - f[x][0] < 0)goto out;
                t += string(c[0] - f[x][0], char(0 + '0'));
                t += ss[x];
                ans = t;
                //cerr << "ok"  << " " << t<< endl;
                return true;
            }
            else if(sum == csum[x] + x){
                string t;
                for(int i = 1;i < 10;i++){
                    if(c[i] - f[x][i] < 0)goto out;
                    t += string(c[i] - f[x][i], char(i + '0'));
                }
                if(c[0] - f[x][0] < 0)goto out;
                t += string(c[0] - f[x][0], char(0 + '0'));
                t += ss[x];
                ans = t;
                //cerr << "ok"  << " " << t<< endl;
                return true;
            }
            
        }
        else{
            int d = digit(x);
            //cerr << x << " " << sum << " " << d << " " << csum[d] << endl;
            if(0 == sum - d - csum[d]){
                //x + d 
                //cerr << "ok " << x << endl;
                string t = to_string(x);
                t += ss[d];
                if(check(t)){
                    ans = t;
                    return true;
                }
            }
            else if(x == sum - d - csum[d]){
                //ans = rem + x + d;
                vector<int>tc(10);
                int y = x;
                while(y){
                    tc[y % 10]++;
                    y /= 10;
                }
                string t;
                for(int i = 1;i < 10;i++){
                    if(c[i] - f[d][i] - tc[i] < 0)goto out;
                    t += string(c[i] - f[d][i] - tc[i], char(i + '0'));
                }
                if(c[0] - f[d][0] - tc[0] < 0)goto out;
                t += string(c[0] - f[d][0] - tc[0], char(0 + '0'));
                t += to_string(x);
                t += ss[d];
                ans = t;
                return true;
            }
            
        }
        out :
        for(int i = 0;i < 10;i++){
            int res = self(self, x * 10 + i, dep + 1);
            if(res)return true;
        }
        return false;
    };

    //dfs(dfs, 252, 1);
    //dfs(dfs, 16, 1);
    //dfs(dfs, 6442, 0);
    for(int i = 1;i < 10;i++){
        if(dfs(dfs, i, 0))break;
    }

    cout << ans << endl;
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