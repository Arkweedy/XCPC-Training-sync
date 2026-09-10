#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//AF.cpp Create time : 2026.08.16 10:16

void solve()
{
    int n = 4;
    vector<int>x = {1,1,1,2,2};
    vector<int>y = {1,2,3,1,3};

    int s = n * n;
    int sum = 1 << s;
    vector<vector<int>>a(n, vector<int>(n));
    int cnt = 0;
    auto check = [&](int cx, int cy)->bool
    {
        int c1 = 0, c2 = 0;
        for(int i = 0;i < cx;i++){
            for(int j = 0;j < cy;j++){
                c1 += a[i][j];
            }
        }
        for(int i = cx;i < n;i++){
            for(int j = cy;j < n;j++){
                c2 += a[i][j];
            }
        }

        if(c1 % 2 == 1 && c2 % 2 == 1)return true;
        else return false;
    };             
    //cerr << "OK" << endl;
    for(int i = 0;i < sum;i++){
        for(int j = 0;j < s;j++){
            int x = j / 4, y = j % 4;
            a[x][y] = ((i >> j) & 1);
        }
        //cerr << "OK" << i << endl;
        // check
        int ok = 1;
        for(int k = 0;k < x.size();k++){
            if(!check(x[k], y[k]))ok = 0;
        }
        //cerr << "OK" << i << endl;
        cnt += ok;
    }
    cerr << cnt << endl;
    cout << __lg(sum / cnt) << endl;

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