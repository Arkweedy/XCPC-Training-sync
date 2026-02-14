#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.13 15:03

void solve()
{
    int n;
    cin >> n;
    vector<i64>a, b, c;
    for(int i = 0;i < n * 2;i++){
        i64 x;
        char y;
        cin >> x >> y;
        if(y == 'R'){
            a.push_back(x);
        }
        else if(y == 'G'){
            b.push_back(x);
        }
        else if(y == 'B'){
            c.push_back(x);
        }
    }
    if(a.size() % 2 == 0 && b.size() % 2 == 0 && c.size() % 2 == 0){
        cout << 0 << endl;
    }
    else{
        if(b.size() % 2 == 0)swap(b, c);
        if(a.size() % 2 == 0)swap(a, c);
        // a, b
        auto calc = [&](vector<i64>a, vector<i64>b)->i64
        {
            sort(a.begin(), a.end());
            sort(b.begin(), b.end());
            int pa = 0, pb = 0;
            if(a.empty() || b.empty())return 1e18;
            i64 res = abs(a[0] - b[0]);
            while(pa < a.size() && pb < b.size()){
                if(a[pa] < b[pb]){
                    pa++;
                }
                else{
                    pb++;
                }
                res = min(res, abs(a[pa] - b[pb]));
            }
            return res;
        };
        // if(same ac, bc, equal to ab)
        i64 res = min(calc(a, b), calc(a, c) + calc(c, b));
        cout << res << endl;
    } 
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