#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.11 22:40

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n), b(n);
    vector<int>p(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        a[i]--;
        p[a[i]] = i;
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
        b[i]--;
    }
    //no : 
    //1. dispart
    //2. cross

    //check apart
    vector<int>vs(n);
    for(int i = 0;i < n;i++){
        if(!vs[b[i]]){
            vs[b[i]] = 1;
        }
        else{
            if(i > 0 && b[i - 1] == b[i]){
                //
            }
            else{
                cout << "NO" << endl;
                return;
            }
        }
    }

    for(int i = 0;i < n - 1;i++){
        if(p[b[i]] > p[b[i + 1]]){
            cout << "NO" << endl;
            return;
        }
    }

    cout << "YES" << endl;
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