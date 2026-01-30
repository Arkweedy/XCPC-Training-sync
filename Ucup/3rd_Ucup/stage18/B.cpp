#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.29 11:03:07

void solve()
{
    int n = 6;
    int m = 10;
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    vector<int>a(n);
    int sum = 0;
    for(int i = 0;i < n;i++){
        a[i] = g() % (m * 2 + 1) - m;
        sum += a[i];
    }
    if(sum == 0)return;

    vector<int>p(n);
    iota(p.begin(),p.end(), 0);

    auto check = [&]()->bool
    {
        
        vector<int>ps(n + 1),ss(n + 1);
        for(int i = 0;i < n;i++){
            ps[i + 1] = ps[i] + a[p[i]];
            if(ps[i + 1] == 0) return false;
        }
        
        for(int i = n - 1;i >= 0;i--){
            ss[i] = ss[i + 1] + a[p[i]];
            if(ss[i] == 0) return false;
        }
        
        return true;
    };
    
    do{
        if(check()){
            cerr << "ok : " ;
            for(auto x : a)cerr << x << " ";
            cerr << endl;
            return;
        }
    }while(next_permutation(p.begin(),p.end()));

    

    cerr << "Outcase : " << endl;
    for(int i = 0;i < n;i++){
        cerr << a[i] << " ";
    }
    cerr << endl;
    assert(0);
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(1){
        solve();
    }
    return 0;
}