#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;

using namespace std;

void solve()
{ 
    int n;
    cin >> n;
    if(n == 1 || n == 3){
        cout << -1 << endl;
        return;
    }

    vector<vector<int>>c(5, vector<int>(5));
    c[0] = {1,2,1,3,1};
    c[1] = {2,1,3,1,1};
    c[2] = {3,1,2,1,1};
    c[3] = {1,3,1,1,2};
    c[4] = {1,1,1,2,3};

    vector<vector<int>>a(n,vector<int>(n));
    i64 sum = n * n;
    if(n % 2 == 0){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                a[i][j] = 1;
            }
        }
    }
    else{
        sum += 3 * n;
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                a[i][j] = 1;
            }
        }
        int m = n / 2 - 2;
        for(int i = 0;i < 5;i++){
            for(int j = 0;j < 5;j++){
                a[m + i][m + j] = c[i][j];
            }
        }
        for(int i=0;i<(n-5)/2;i++){
            a[i][i] = a[n-1-i][n-1-i] = 2;
            a[i][n-1-i] = a[n-1-i][i] = 3;
        }
        // if(n>5){
        //     a[0][0] = a[n-1][n-1] = 2;
        //     a[0][n-1] = a[n-1][0] = 3;
        // }
    }
    cout << sum << "\n";
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }

    auto  check = [&]() -> int
    {
        //if(!a[3][3]) return 0;
        int o=0;
        for(int i=0;i<n;i++){
            o=0;
            for(int j=0;j<n;j++) o^=a[i][j];
            if(o) return 2;
        }
        for(int j=0;j<n;j++)
            {
                int o=0;
                for(int i=0;i<n;i++) o^=a[i][j];
                if(o) return 3;
            }
        o=0;
        for(int i=0;i<n;i++) o^=a[i][i];
        if(o) return 4;
        o=0;
        for(int i=0;i<n;i++) o^=a[i][n-1-i];
        if(o) return 5;
        return 1;
    };
    //cout<<check()<<endl;
    if(check()!=1){
        cerr << "WA" << endl;
    }

    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}