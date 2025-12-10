#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

// vector<int>Duval(const string& s)
// {
//     int n = s.length();
//     vector<int>lyn;//
//     for(int i = 0;i < n;){
//         int j = i + 1, k = i;
//         while(j < n && s[k] <= s[j]){
//             if(s[j] > s[k])k = i;
//             else k++;
//             j++;
//         }
//         while(i <= k){//i + j - k <= j
//             i += j - k;
//             lyn.push_back(i - 1);
//         }
//     }
//     return lyn;
// };

vector<pair<int,int>>Duval(const string& s)
{
    int n = s.length();
    vector<pair<int,int>>lyn;//
    for(int i = 0;i < n;){
        int j = i + 1, k = i;
        while(j < n && s[k] <= s[j]){
            if(s[j] > s[k])k = i;
            else k++;
            j++;
        }
        while(i <= k){//i + j - k <= j
            lyn.emplace_back(i, i + j - k - 1);
            i += j - k;
        }
    }
    return lyn;
};

void solve()
{
    string s;
    cin>>s;
    auto lyn = Duval(s);
    // for(auto [l, r] : lyn){
    //     cerr<<s.substr(l, r - l + 1)<<endl;
    // }


    int ans = 0;
    for(auto [l,r] : lyn){
        ans ^= r + 1;
        //cerr<<x + 1<<endl;
    }
    cout<<ans<<endl;
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