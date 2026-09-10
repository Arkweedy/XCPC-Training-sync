#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//K.cpp Create time : 2026.07.26 13:37

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int>a, b;
    int c = 0;
    for(int i = 0;i < k - 1;i++){
        if(s[i] == '1'){
            cout << -1 << "\n";
            return;
        }
    }

    vector<int>ans, op;
    auto add = [&](int x, int y)->void
    {
        ans.push_back(x);
        op.push_back(y);
    };

    if(k == 1){
        if(s[0] == '0'){
            cout << -1 << "\n";
            return;
        }
        else{
            add(1, 1);
            vector<int>buf(1, 1);
            for(int i = 1;i < n;i++){
                if(s[i] == '1'){
                    while(!buf.empty()){
                        add(buf.back(), -1);
                        //cout << "O " << buf.back() << "\n";
                        buf.pop_back();
                    }
                    add(i + 1, 1);
                    //cout << "I " << i + 1 << "\n";
                    buf.push_back(i + 1);
                }
                else{
                    add(i + 1, 1);
                    //cout << "I " << i + 1 << "\n";
                    buf.push_back(i + 1);
                }
            }
        }
    }
    else{
        vector<int>buf;
        for(int i = 0;i < k - 1;i++){
            add(i + 1, 1);
            //cout << "I " << i + 1 << "\n";
            buf.push_back(i + 1);
        }
        for(int i = k - 1;i < n;i++){
            if(s[i] == '1'){
                add(i + 1, 1);
                //cout << "I " << i + 1 << "\n";
                buf.push_back(i + 1);
                add(buf.back(), -1);
                //cout << "O " << buf.back() << "\n";
                buf.pop_back();
            }
            else{
                add(buf.back(), -1);
                //cout << "O " << buf.back() << "\n";
                buf.pop_back();
                add(i + 1, 1);
                //cout << "I " << i + 1 << "\n";
                buf.push_back(i + 1);
            }
        }
    }

    cout << ans.size() << "\n";
    for(int i = 0;i < ans.size();i++){
        if(op[i] == 1){
            cout << "I " << ans[i] << "\n";
        }
        else{
            cout << "O " << ans[i] << "\n";
        }
    }
    return;

    // if(c <= n - k + 1){
    //     int cnt = b.size() + a.size() * 2 - 1;
    //     cout << cnt << "\n";
    //     for(int i = 0;i < k - 1;i++){
    //         cout << "I " << b[i] + 1 << "\n";
    //     }
    //     for(int i = 0;i < a.size();i++){
    //         cout << "I " << a[i] + 1 << "\n";
    //         if(i != a.size() - 1)cout << "O " << a[i] + 1 << "\n";
    //     }
    //     for(int i = k - 1;i < b.size();i++){
    //         cout << "I " << b[i] + 1 << "\n";
    //     }
    // }
    // else{
    //     cout << -1 << "\n";
    // }
    // return;
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