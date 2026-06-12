#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.06.09 22:52

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    auto calc = [&](vector<int>a)->int
    {
        int ans = 0, c = 0;
        for(int i = 0;i < n;i++){
            if(a[i] == 1)continue;
            if(s[i] == '(')c++;
            if(s[i] == ')' && c > 0){
                c--;
                ans++;
            }
        }
        return ans;
    };
    vector<int>l,r;
    for(int i = 0;i < n;i++){
        if(s[i] == '(')l.push_back(i);
        else r.push_back(i);
    }
    reverse(r.begin(),r.end());
    
    vector<int>ans;
    int res = n;
    for(int i = 0;i <= k;i++){
        vector<int>a(n);
        for(int j = 0;j < i && j < l.size();j++){
            a[l[j]] = 1;
        }
        for(int j = 0;j < k - i && j < r.size();j++){
            a[r[j]] = 1;
        }
        int cnt = calc(a);
        if(cnt < res){
            res = cnt;
            ans = a;
        }
    }
    for(int i = 0;i < n;i++){
        cout << ans[i];
    }
    cout << endl;
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