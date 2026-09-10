#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.07.16 23:11

void solve()
{
    int n, k;
    cin >> n >> k;
    int mexxor = n;
    vector<int>mex;
    mex.push_back(n);
    int p = 30;
    while(p >= 0 && !((k ^ mexxor) >> p))p--;
    for(int i = n - 1;i >= 1;i--){
        if(i < (1 << p + 1)){
            mexxor ^= i;
            mex.push_back(i);
            while(p >= 0 && !((k ^ mexxor) >> p))p--;
        }
        if(p == -1){
            break;
        }
    }
    if(mexxor != k){
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    vector<int>use(n), ans(n, 0);
    for(int i = 1;i < mex.size();i++){
        ans[n - i] = mex[i];
        use[mex[i]] = 1;
    }
    p = 1;
    for(int i = 0;i < n;i++){
        while(p < n && use[p])p++;
        if(p == n)break;
        ans[i] = p;
        use[p] = 1;
    }
    for(int i = 0;i < n;i++){
        cout << ans[i] << " ";
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