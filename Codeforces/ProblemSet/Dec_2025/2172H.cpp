#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//2500string.cpp Create time : 2025.12.22 15:06

void solve()
{
    int k, t;
    cin >> k >> t;
    string s;
    cin >> s;

    vector<int>a(1 << k);
    iota(a.begin(),a.end(), 0);
    auto merge = [&](vector<int>a, vector<int>b)->vector<int>
    {
        vector<int>c(1 << k);
        for(int i = 0;i < a.size();i++){
            c[i] = a[b[i]];
        }
        return c;
    };

    vector<int>b(1 << k);
    for(int i = 0;i < (1 << k);i++){
        if(i % 2 == 0){
            b[i] = a[i / 2];
        }
        else{
            b[i] = a[i / 2 + (1 << k - 1)];
        }
    }


    vector<int>res1 = a, res2 = a;
    for(int i = 0;i < t;i++){
        res2 = merge(res2, b);
        if(res2 == a)cerr << i << endl;
    }
    while(t){
        if(t & 1)res1 = merge(res1, b);
        b = merge(b, b);
        t >>= 1;
    }
    assert(res1 == res2);
    for(int i = 0;i < (1 << k);i++){
        cerr << res1[i] << " ";
    }
    cerr << endl;

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