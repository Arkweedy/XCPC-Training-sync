#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.08.11 14:34:46

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    vector<vector<int>>b(n + 1, vector<int>(m, -1));

    vector<int>dx = {1,1,1,0,0,-1,-1,-1}, dy = {1,0,-1,1,-1,1,0,-1};
    int cnt = 0;
    int sum = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(a[i][j] == '#'){
                b[i][j] = -1;
                sum++;
            }
            else if(a[i][j] == '?' || a[i][j] == 'Q'){
                b[i][j] = -1;
            }
            else{
                for(int k = 0;k < 8;k++){
                    int x = i + dx[k], y = j + dy[k];
                    if(x >= 0 && x < n && y >= 0 && y < m){
                        if(a[x][y] == '#'){
                            b[i][j]++;
                        }
                    }
                }
            }
        }
    }

    vector<vector<int>>c(n + 1, vector<int>(m))
    vector<vector<int>>con(n, vector<int>(m, -1));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(a[i][j] == '#'){
                c[i][j] = 1;
            }
            else if(a[i][j] == 'O' || a[i][j] == 'Q'){
                con[i][j] = b[i][j];
                c[i][j] = 0;
            }
            else{
                c[i][j] = 1;
            }
        }
    }

    auto calc = [&]()->void
    {
        vector<int>msk;
        for(int i = 0;i <= n;i++){
            int fmsk = 0;
            for(int j = 0;j < m;j++){
                if(c[i][j] == 1)fmsk |= (1 << j);
            }
            vector<int>lo;
            for(int s = fmsk; s != 0;s = (s - 1) & fsmk){
                lo.push_back(s);
            }
            lo.push_back(0);

            if(i == 0){
                msk = move(lo);
            }
            else{
                for(auto A : msk){
                    int H = (A >> m), M = A - (H << m);
                    for(auto L : lo){
                        
                    }
                }
            }
        }
    };

    
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