#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.15 14:01

// p_i | presum_i

//2 1 3
//3 1 4 2
//3 1 4 2 5
//2 4 6 3 5 1
//2 4 6 3 5 7 1
//8 4 3 5 1 7 2 6

// if(2k + 1) append
// if(2k)? delete k ? 





void solve()
{
    int n;
    cin >> n;
    cout << "YES" << endl;
    if(n == 1){
        cout << 1 << endl;
    }
    else if(n == 2){
        cout << "2 1" << endl;
    }
    else if(n == 3){
        cout << "2 1 3" << endl;
    }
    else if(n >= 4){
        int m = n / 2 * 2;
        vector<int>a(m);
        for(int i = 0;i < m;i++){
            if(i % 2 == 0)a[i] = m / 2 + i / 2 + 1;
            else a[i] = i / 2 + 1;
        }
        if(n % 2 == 1)a.push_back(n);
        for(int i = 0;i < n;i++){
            cout << a[i] << " ";
        }
        cout << endl;
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