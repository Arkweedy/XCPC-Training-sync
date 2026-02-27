#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.25 23:14

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>ca(n + m + 1), cb(n + m + 1);
    vector<int>a(n), b(m);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        ca[a[i]]++;
    }
    for(int i = 0;i < m;i++){
        cin >> b[i];
        cb[b[i]]++;
    }
    // Alice : 
    // compare cnt ya and yb
    vector<int>d(n + m + 1);
    for(int i = 1;i <= n + m;i++){
        if(ca[i]){
            for(int j = 1;j * i <= n + m;j++){
                d[i * j] += ca[i];
            }
        }
    }
    int alc = 0, bob = 0, ab = 0;
    for(int i = 1;i <= n + m;i++){
        if(d[i] == n){
            alc += cb[i];
        }
        else if(d[i] == 0){
            bob += cb[i];
        }
        else{
            ab += cb[i];
        }
    }
    if(alc + (ab % 2) <= bob){
        cout << "Bob" << endl;
    }
    else{
        cout << "Alice" << endl;
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