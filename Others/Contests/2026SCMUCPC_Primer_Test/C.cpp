#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.05.09 19:08

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int>a(n), ex(n, 1);
    i64 sum = 0;
    int cnt = n;
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    while(q--){
        string op;
        cin >> op;
        if(op[0] == 'C' && op[1] == 'H'){
            cout << cnt << endl;
        }
        else if(op[0] == 'C' && op[1] == 'A'){
            cout << sum << endl;
        }
        else if(op[0] == 'B'){
            int x;
            cin >> x;
            x--;
            if(ex[x]){
                sum += a[x];
                cnt--;
                ex[x] = false;
            }
            else{
                cout << "ERROR" << endl;
            }
        }
        else if(op[0] == 'R'){
            int x;
            cin >> x;
            x--;
            if(ex[x]){ 
                cout << "ERROR" << endl;
            }
            else{
                sum -= a[x];
                cnt++;
                ex[x] = true;
            }
        }
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