#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.05.27 14:28

void solve()
{
    int n;
    cin >> n;
    vector<int>op(n),a(n),b(n);
    
    for(int i = 0;i < n;i++){
        string s;
        cin >> s;
        if(s[0] == 'a'){
            op[i] = 0;
            int x;
            cin >> x;
            a[i] = x;
        }
        else{
            int x, y;
            cin >> x >> y;
            a[i] = x;
            b[i] = y;
            b[i]--;
            if(s[1] == 'e'){
                op[i] = 1;
            }
            else if(s[1] == 'n'){
                op[i] = 2;
            }
            else if(s[1] == 'l'){
                op[i] = 3;
            }
            else if(s[1] == 'g'){
                op[i] = 4;
            }
        }
    }

    constexpr int M = 256;
    vector<int>vs(n * M);
    int p = 0, v = 0;
    while(1){
        //cerr << p << " "  << v << " " << op[p] << endl;
        if(p >= n)break;
        int st = p * M + v;
        if(vs[st])break;
        vs[st] = 1;
        if(op[p] == 0){
            v = (v + a[p]) % M;
            p++;
        }
        else if(op[p] == 1){
            if(v == a[p]){
                p = b[p];
            }
            else{
                p++;
            }
        }
        else if(op[p] == 2){
            if(v != a[p]){
                p = b[p];
            }
            else{
                p++;
            }
        }
        else if(op[p] == 3){
            if(v < a[p]){
                p = b[p];
            }
            else{
                p++;
            }
        }
        else if(op[p] == 4){
            if(v > a[p]){
                p = b[p];
            }
            else{
                p++;
            }
        }
    }
    if(p < n){
        cout << "No" << endl;
    }
    else{
        cout << "Yes" << endl;
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