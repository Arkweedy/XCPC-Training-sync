#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.25 22:48

void solve()
{
    i64 s , m;
    cin >> s >> m;
    vector<int>msk, tar;
    for(int i = 61;i >= 0;i--){
        if((m >> i) & 1)msk.push_back(i);
        if((s >> i) & 1)tar.push_back(i);
    }

    auto check = [&](i64 k)->int
    {
        int pm = 0, ps = 0;
        i128 nowcnt = -1;
        i64 rem = -1; 
        while(pm < msk.size() && ps < tar.size()){
            if(nowcnt == -1)nowcnt = (1ll << msk[pm]) * (i128)k;
            if(rem == -1)rem = 1ll << tar[ps];
            if(msk[pm] > tar[ps]){
                pm++;
                nowcnt = -1;
            }
            else{//leq
                if(nowcnt > rem){
                    nowcnt -= rem;
                    ps++;
                    rem = -1;
                }
                else if(nowcnt == rem){
                    pm++;
                    ps++;
                    rem = -1;
                    nowcnt = -1;
                }
                else{
                    rem -= nowcnt;
                    pm++;
                    nowcnt = -1;
                }
            }
        }
        if(ps == tar.size())return true;
        else return false;
    };

    i64 l = 0, r = s + 1;
    while(r - l > 1){
        i64 mid = l + r >> 1;
        if(check(mid)){
            r = mid;
        }
        else{
            l = mid;
        }
    }
    if(r == s + 1){
        cout << -1 << endl;
    }
    else{
        cout << r << endl;
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