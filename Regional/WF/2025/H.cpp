#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.25 16:57:32

void solve()
{
    i64 m;
    int n;
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    //cin >> m >> n;
    m = 1e9;
    n = 2;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        //cin >> a[i];
        a[i] = g() % 1000 + 1;
        cerr << a[i] << " ";
    }
    cerr << endl;

    constexpr int N = 1e6;
    vector<int>mi(N, -1);
    priority_queue<int,vector<int>,greater<int>>pq;
    pq.push(0);
    while(!pq.empty()){
        int p = pq.top();
        pq.pop();
        if(mi[p % N] != -1)continue;
        mi[p % N] = p;
        for(int i = 0;i < n;i++){
            pq.push(p + a[i]);
        }
    }

    int h = -1;
    for(int i = 1;i < N;i++){
        if(mi[i] == i && N % i == 0){
            h = i;
            break;
        }
    }
    cerr << "h = " << h << endl;

    
    int x = g() % 1000;

    auto check = [&](int x)->void
    {
        cerr << "check " << x << endl;
        for(int i = x;i < N;i += 1000){
            cerr  << i  << " : " << mi[i] << endl;
        }
        return;
    };

    check(x);

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