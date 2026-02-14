#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.13 15:31

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        a[i]--;
    }
    int op = 0;
    vector<int>ans;
    auto sw = [&](int p)->void
    {
        assert((p & 1) == op);
        ans.push_back(p + 1);
        swap(a[p], a[p + 1]);
        op ^= 1;
    };

    for(int i = 0;i < n + 100;i++){
        for(int j = 0;j < n - 1;j++){
            if(a[j] > a[j + 1]){
                if((j & 1) == op){
                    sw(j);
                }
                else{
                    sw(op);
                    sw(j);
                }
            }
        }
    }

    assert(ans.size() <= n * n);
    cout << ans.size() << endl;
    for(auto x : ans)cout << x << " ";
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