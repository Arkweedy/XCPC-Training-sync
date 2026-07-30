#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.29 13:29:51

int Duval(const vector<int>& s)//return begin of min expression
{
    int n = s.size();
    int last = -1;
    for(int i = 0;i < n;){
        int j = i + 1, k = i;
        while(j < n && s[k] <= s[j]){
            if(s[j] > s[k])k = i;
            else k++;
            j++;
        }
        
        last = i;
        while(i <= k){//i + j - k <= j
            i += j - k;
        }
        if(j == n)break;//find last but not empty
    }
    return last;
};

vector<int> minExpr(const vector<int>&a)
{
    int n = a.size();
    int p = Duval(a);
    vector<int>res(n);
    for(int i = 0;i < n;i++){
        if(i + p < n)res[i] = a[i + p];
        else res[i] = a[i + p - n];
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    auto dfs = [&](this auto&&dfs, int p, vector<int>pi, vector<int>use)->pair<vector<int>, vector<int>>
    {
        if(p == n)return {pi, minExpr(pi)};
        vector<int>res, minp;
        for(int i = 1;i <= n;i++){
            if(!use[i]){
                auto nuse = use;
                auto npi = pi;
                npi.push_back(i);
                nuse[i] = 1;
                auto [per, mi] = dfs(p + 1, npi, nuse);
                if(p % 2 == 0){// min
                    if(res.empty() || mi < minp){
                        res = per;
                        minp = mi;
                    }
                }
                else{
                    if(res.empty() || mi > minp){
                        res = per;
                        minp = mi;
                    }
                }
            }
        }
        return {res, minp};
    };

    auto [res, minp] = dfs(0, vector<int>(0), vector<int>(n + 1, 0));
    for(auto x : res){
        cout << x << " ";
    }
    cout << endl;
    for(auto x : minp){
        cerr << x << " ";
    }
    cerr << endl;
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