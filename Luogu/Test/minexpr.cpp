#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//minexpr.cpp Create time : 2026.09.04 01:52

int Duval(const string& s)//return begin of min expression
{
    int n = s.length();
    string t = s + s;
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

void solve()
{
    string s;
    cin >> s;
    cout << Duval(s) << endl;
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