#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.29 12:46:40

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>a(n, vector<int>(m));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin >> a[i][j];
        }
    }

    multiset<int>A;
    set<pair<int, int>>B;
    for(int j = 0;j < m;j++){
        for(int i = 0;i < n;i++){
            B.insert(make_pair(a[i][j], j * n + i));
        }
    }

    vector<vector<int>>ex(n,vector<int>(m, 1));

    auto check = [&](int k)->int
    {
        vector<int>x(k),y(k);
        auto ita = prev(A.end());
        auto itb = B.begin();
        for(int i = 0;i < k;i++){
            x[i] = *ita;
            ita--;
        }
        for(int i = k - 1;i >= 0;i--){
            y[i] = (*itb).first;
            itb++;
        }
        for(int i = 0;i < k;i++){
            if(x[i] <= y[i])return false;
        }
        return true;
    };

    auto erase = [&](int k)->void
    {
        auto itb = B.begin();
        vector<pair<int,int>>pr(k);
        for(int i = 0;i < k;i++){
            auto [v, p] = *itb;
            pr[i] = *itb;
            int y = p / n, x = p % n;
            ex[x][y] = 0;
            itb++;
        }
        for(auto p : pr){
            //cerr << "erase " << p.first << " " << p.second / n << " " << p.second % n << endl;
            B.erase(p);
        }
        A.clear();
    };

    int sum = 0;
    int cb = n * m;
    for(int j = 0;j < m;j++){
        int ca = 0;
        for(int i = 0;i < n;i++){
            if(ex[i][j]){
                A.insert(a[i][j]);
                B.extract(make_pair(a[i][j], j * n + i));
                ca++;
                cb--;
            }
        }
        
        int l = 0, r = min(ca, cb) + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            if(check(m)){
                l = m;
            }
            else{
                r = m;
            }
        }
        sum += l;
        
        //cerr << "pre" << endl;
        //cerr << ca << " " << cb << endl;
        //cerr << A.size() << " " << B.size() << endl;
        // for(auto x : A){
        //     cerr << x << " ";
        // }
        // cerr << endl;
        // for(auto [x, y] : B){
        //     cerr << x << " ";
        // }
        // cerr << endl;
        
        erase(l);
        //cerr << "ok" << endl;
        cb -= l;
    }

    if(sum >= n){
        cout << "YES" << "\n";
    }
    else{
        cout << "NO" << "\n";
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