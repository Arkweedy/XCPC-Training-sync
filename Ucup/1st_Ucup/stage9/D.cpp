#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.28 12:57:33

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>a, b;
    string s;
    cin >> s;
    auto check = [&](int x)->bool
    {
        
        a.assign(n, -1);
        b.assign(m, -1);
        a[0] = x;
        int p = 0;
        for(int i = 0;i < m;i++){
            for(int j = 0;j <= 9;j++){
                string t = to_string(a[0] * j);
                if(s.substr(p, t.size()) == t){
                    b[i] = j;
                    p += t.size();
                    break;
                }
            }
            if(b[i] == -1){
                return false;
            }
            if(i == 0 && b[i] == 0){
                return false;
            }
        }

        for(int i = 1;i < n;i++){
            for(int j = 0;j <= 9;j++){
                string t = to_string(b[0] * j);
                
                if(s.substr(p, t.size()) == t){
                    a[i] = j;
                    p += t.size();
                    break;
                }
            }
            if(a[i] == -1){
                return false;
            }
            for(int j = 1;j < m;j++){
                string t = to_string(a[i] * b[j]);
                if(s.substr(p, t.size()) != t){
                    return false;
                }
                else{
                    p += t.size();
                }
            }
        }
        return p == s.size();
    };

    //check(2);

    for(int i = 1;i <= 9;i++){
        if(check(i)){
            for(auto x : a)cout << x;
            cout << " ";
            for(auto x : b)cout << x;
            cout << endl;
            return;
        }
    }

    cout << "Impossible" << endl;
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