#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.09 00:26:00

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>ok(n + 2, 1);
    for(int i = 0;i < n;i++){
        ok[a[i]] = false;
    }

    // decrease -> same 
    // equal -> dif

    vector<int>ans(n);
    vector<int>chs(n);
    int same = 0;
    int free = 0;
    int p = 0;
    int t = 0;
    if(a[0] == n - 1){
        ans[0] = n;
        p++;
    }
    else{
        free++;
    }
    
    for(int i = 1;i < n;i++){
        cerr << i << endl;
        if(a[i] == a[i - 1]){
            free++;
        }
        else{
            cerr << a[i - 1] << " " << a[i] + 1 << endl;
            for(int j = a[i] + 1;j < a[i - 1];j++){
                cerr << "in" << endl;
                cerr << j << endl;
                ans[p++] = j;
                free--;
                if(free < 0){
                    cout << "NO" <<endl;
                    return;
                }
            }
        }
    }
    while(p < n){
        ans[p++] = ans[p - 1];
    }
    cout <<"YES" << endl;
    for(int i = 0;i < n;i++){
        cout << ans[i] << " " ;
    }
    cout << endl;
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