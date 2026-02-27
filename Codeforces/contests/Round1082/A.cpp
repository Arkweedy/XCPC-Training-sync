#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.02.23 22:34

void solve()
{
    int x, y;
    cin >> x >> y;
    if((x + y) % 3 != 0){
        cout << "No" << "\n";
        return;
    }

    if(y >= 0){
        int lx = y * 2;
        if(x >= lx && (x - lx) % 3 == 0){
            cout << "Yes" << endl;
        }
        else{
            cout << "No" << endl;
        }
    }
    else{
        int lx = -y * 4;
        if(x >= lx && (x - lx) % 3 == 0){
            cout << "Yes" << endl;
        }
        else{
            cout << "No" << endl;
        }
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