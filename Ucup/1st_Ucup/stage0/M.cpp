#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//M.cpp Create time : 2026.03.04 11:15

void solve()
{
    int n;
    cin >> n;
    vector<int>x(n), y(n);
    for(int i = 0;i < n;i++){
        cin >> x[i] >> y[i];
    }
    x.push_back(x[0]);
    y.push_back(y[0]);
    n++;
    vector<int>nx, ny;
    nx.push_back(x[0]);
    nx.push_back(x[1]);
    ny.push_back(y[0]);
    ny.push_back(y[1]);
    for(int i = 2;i < n;i++){
        int m = nx.size();
        if(x[i] == nx[m - 1] && x[i] == nx[m - 2]){
            nx.pop_back();
            ny.pop_back();
        }
        else if(y[i] == ny[m - 1] && y[i] == ny[m - 2]){
            nx.pop_back();
            ny.pop_back();
        }
        nx.push_back(x[i]);
        ny.push_back(y[i]);
    }
    nx.pop_back();
    ny.pop_back();
    x = move(nx);
    y = move(ny);
    n = x.size();

    int ans = 0;
    for(int i = 0;i < n;i++){
        //cerr << x[i] << " " << y[i] << endl;
        if(y[(i + 1) % n] < y[i] && y[(i + 1) % n] <= y[(i + 2) % n]){
            if((x[i] < x[(i + 2) % n]) || (x[(i + 1) % n] > x[(i + 2) % n] && x[i] > x[(i + 2) % n]) || (x[(i + 1) % n] < x[(i + 2) % n] && x[i] < x[(i + 2) % n])){
                if(y[(i + 1) % n] == y[(i + 2) % n]){
                    if(y[(i + 2) % n] < y[(i + 3) % n]){
                        ans++;
                    }
                }
                else{
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
    return;
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