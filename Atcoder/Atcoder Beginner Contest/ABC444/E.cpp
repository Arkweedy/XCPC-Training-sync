#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.07 20:24

void solve()
{
    int n, d;
    cin >> n >> d;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    set<int>s;
   

    auto check = [&](int i)->bool
    {
        auto it = s.upper_bound(a[i]);
        //check after
        int ok = 0;
        if(it == s.end() || *it >= a[i] + d){
            ok++;
        }
        //check prev
        if(it == s.begin() || *(prev(it)) + d <= a[i]){
            ok++;
        }
        if(ok == 2)return true;
        else return false;
    };


    int p = 0;
    vector<int>r(n);
    for(int i = 0;i < n;i++){
        while(!s.empty() && !check(i)){
            r[p] = i - 1;
            s.erase(a[p]);
            p++;
        }
        s.insert(a[i]);
    }
    for(int i = p;i < n;i++){
        r[i] = n - 1;
    }
    i64 ans = 0;
    for(int i = 0;i < n;i++){
        ans += r[i] - i + 1;
    }
    cout << ans << endl;
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