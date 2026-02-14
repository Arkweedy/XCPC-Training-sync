#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.14 20:09

int power(int a, int p, int m)
{
    int res = 1 % m;
    while(p){
        if(p & 1)res = 1ll * res * a % m;
        a = 1ll * a * a % m;
        p >>= 1;
    }
    return res;
}

//find circle/list

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        a[i]--;
    }

    int len = 235;
    vector<vector<int>>ne(n, vector<int>(len));
    for(int i = 0;i < n;i++){
        ne[i][0] = a[i];
    }
    for(int j = 1;j < len;j++){
        for(int i = 0;i < n;i++){
            ne[i][j] = ne[ne[i][j - 1]][j - 1];
        }
    }

    string s = "1";
    auto mul5 = [&]()->void
    {
        auto t = "00" + s + "00";
        int carry = 0;
        for(int i = 0;i < t.size() - 1;i++){
            int sum = 0;
            if(i < s.size()){
                sum += s[i] - '0';
            }
            sum += carry + t[i] - '0';
            if(sum >= 2)carry = 1;
            else carry = 0;
            if(sum % 2 == 0)t[i] = '0';
            else t[i] = '1';
        }
        while(t.back() == '0')t.pop_back();
        s = t;
    };

    for(int i = 0;i < 100;i++){
        mul5();
    }

    // cerr << s.size() <<  " " << len << endl;
    // cerr << s << endl;

    vector<int>ans(n);
    iota(ans.begin(),ans.end(), 0);
    for(int i = 0;i < s.size();i++){
        if(s[i] == '1'){
            for(int j = 0;j < n;j++){
                ans[j] = ne[ans[j]][i];
            }
        }
    }

    for(int i = 0;i < n;i++){
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return;

    // vector<vector<int>>p;
    // vector<int>t;
    // vector<int>vs(n);
    // vector<int>id(n);
    // vector<int>ord(n);
    // vector<int>fa(n);
    // vector<vector<int>>lis;
    // int tot = 0;
    // int pid = 0;
    // auto dfs = [&](auto&&self, int p)->void
    // {
    //     if(vs[p])return;
    //     vs[p] = 1;
    //     id[p] = pid;
    //     t.push_back(p);
    //     ord[p] = tot++;
    //     self(self, a[p]);
    //     return;
    // };


    // for(int i = 0;i < n;i++){
    //     if(!vs[i]){
    //         dfs(dfs, i);
    //         tot = 0;
    //         pid++;
    //         p.emplace_back(t);
    //         t.clear();
    //     }
    // }

    
    // vector<int>ans(n);
    // for(int i = 0;i < n;i++){
    //     int m = p[id[i]].size();
    //     int r = power(10, 100, m);
    //     ans[i] = p[id[i]][(ord[i] + r) % m];
    // }
    // for(int i = 0;i < n;i++){
    //     cerr << p[id[i]].size(); 
    //     cout << ans[i] + 1 << " ";
    // }
    // cout << endl;
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