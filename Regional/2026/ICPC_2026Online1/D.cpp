#include <bits/stdc++.h>
using ll = long long;
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int>c(n);
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        c[x]++;
    }

    auto check = [&](int msk)->bool
    {
        int a = 0, b = 0;
        auto cc = c;
        for(int i = 0;i < n;i++){
            if((msk >> i) & 1){
                a++;
                cc[b]--;
            }
            else{
                b++;
                cc[a]--;
            }
        }
        for(int i = 0;i < n;i++){
            if(cc[i] != 0)return false;
        }
        return true;
    };

    int ans = 0;
    for(int i = 0;i < (1 << n);i++){
        ans += check(i);
    }
    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}