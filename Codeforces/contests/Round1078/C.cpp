#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.08 17:34

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<string>s(k);
    for(int i = 0;i < k;i++){
        cin >> s[i];
    }
    vector<int>factor;
    for(int i = 1;i * i <= n;i++){
        if(n % i == 0){
            factor.push_back(i);
            if(i * i != n){
                factor.push_back(n / i);
            }
        }
    }
    sort(factor.begin(),factor.end(), less<>());

    for(auto d : factor){
        int ok = 1;
        string ans(n, ' ');
        for(int i = 0;i < d;i++){
            vector<int>ex(26, 1);
            for(int j = 0;j < n / d;j++){
                vector<int>nex(26, 0);
                for(int t = 0;t < k;t++){
                    int e = s[t][i + j * d] - 'a';
                    nex[e] = 1;
                }
                for(int t = 0;t < 26;t++){
                    ex[t] &= nex[t];
                }
            }
            if(count(ex.begin(),ex.end(), 1) == 0){
                ok = 0;
                break;
            }
            else{
                int p = 0;
                while(!ex[p])p++;
                char c = p + 'a';
                for(int j = 0;j < n / d;j++){
                    ans[i + j * d] = c;
                }
            }
        }
        if(ok){
            cout << ans << endl;
            return;
        }
    }

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