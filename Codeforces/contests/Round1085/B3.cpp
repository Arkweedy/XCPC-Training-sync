#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.08 23:10:55

void solve()
{
    int n, m, l;
    cin >> n >> m >> l;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    multiset<int>s;
    int c = min(n + 1, m);
    for(int i = 0;i < c;i++){
        s.insert(0);
    }
    int p = 1;
    for(int i = 1;i <= l;i++){
        //cerr << "i = " << i << endl;
        int x = *s.begin();
        s.extract(x);
        x++;
        s.insert(x);
        if(p <= n && a[p] == i){
            
            int x = *prev(s.end());
            s.extract(x);
            if(n - p + 1 < m){
                //cerr << n << " " << p << endl;
            }
            else{
                s.insert(0);
            }
            p++;
        }
        
    }
    int ans = *prev(s.end());
    cout << ans << endl;
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