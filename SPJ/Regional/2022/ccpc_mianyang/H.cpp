#include<bits/stdc++.h>
using ll = long long;
using namespace std;

constexpr int N = 1e5;

void solve()
{
    constexpr int n = 100;
    vector<vector<int>>a(n + 1,vector<int>(n + 1));

    int xx;
    cin>>xx;
    for(int i = 0;i < xx;i++){
        int x, y;
        cin>>x>>y;
        a[x][y] = 1;        
    }

    vector<vector<int>>emp(n + 1,vector<int>(n + 1));
    int time = 0;
    constexpr int m = 10;
    auto print = [&]()->void
    {
        //system("cls");
        cout<<"Time "<<time<<endl;
        for(int i = 0;i < m;i++){
            for(int j = 0;j < m;j++){
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        return;
    };

    auto around = [&](int x, int y)->int
    {
        int res = 0;
        for(int i = max(0, x - 1);i <= min(x + 1, n);i++){
            for(int j = max(0, y - 1);j <= min(y + 1, n);j++){
                res += a[i][j];
            }
        }
        res -= a[x][y];
        return res;
    };

    auto next = [&]()->void
    {
        vector<vector<int>>na(n + 1,vector<int>(n + 1));
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                int c = around(i, j);
                if(a[i][j]){
                    if(c >= 2 && c <= 3)na[i][j] = 1;
                    else na[i][j] = 0;
                }
                else{
                    if(c == 3)na[i][j] = 1;
                    else na[i][j] = 0;
                }
            }
        }
        a = move(na);
        time++;
        return;
    };

    print();
    while(1){
        next();
        print();
        if(time == 20)break;
        if(a == emp)break;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while (tt--)
    {
        solve();
    }
    return 0;    
}
