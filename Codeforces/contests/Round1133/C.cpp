#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.11.07 22:48

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>d(n);
    int p = 0;
    int ma = 0;
    for(int i = 0;i < n - 1;i++){
        d[i] = abs(a[i + 1] - a[i]);
        if(ma <= d[i]){
            ma = d[i];
            p = i;
        }
    }
    // p | p + 1
    vector<int>Lans(n),Rans(n);
    Lans[0] = d[0];
    for(int i = 1;i < p;i++){
        Lans[i] = max(Lans[i - 1], d[i]);
    }
    for(int i = n - 2;i >= p + 1;i--){
        Rans[i] = max(Rans[i + 1], d[i]);
    }

    auto getL = [&](int L)->int
    {
        if(L < 0)return 0;
        else return Lans[L];
    };

    auto getR = [&](int R)->int
    {
        if(R > n - 1)return 0;
        else return Rans[R];
    };

    auto dif = [&](int i, int j)->int
    {
        if(i < 0 || i >= n || j < 0 || j >= n)return 0;
        return abs(a[i] - a[j] * 2);
    };

    int ans = ma;
    int Lin = 0, Rin = 0;
    for(int i = p;i >= 0;i--){
        if(i != p)Lin = max(Lin, d[i] * 2);
        int nma = max(max(getR(p + 1), getL(i - 2)), max(dif(p + 1, i), dif(i - 1, p)));
        nma = max(nma, Lin);
        ans = min(ans, nma);
    }
    for(int i = p + 1;i < n;i++){
        if(i != p + 1)Rin = max(Rin, d[i - 1] * 2);
        int nma = max(max(getL(p - 1), getR(i + 1)),  max(dif(p, i), dif(i + 1, p + 1)));
        nma = max(nma, Rin);
        ans = min(ans, nma);
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