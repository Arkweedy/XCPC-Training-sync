#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B2.cpp Create time : 2026.02.15 14:35

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    iota(a.begin(),a.end(), 1);
    auto check = [&]()->bool
    {
        int sum = 0;
        for(int i = 0;i < n;i++){
            sum += a[i];
            if(sum % a[i] != 0)return false;
        }
        return true;
    };

    while(next_permutation(a.begin(),a.end())){
        if(check()){
            for(int i = 0;i < n;i++){
                cout << a[i] << " ";
            }
            cout << endl;
        }
    }
    
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