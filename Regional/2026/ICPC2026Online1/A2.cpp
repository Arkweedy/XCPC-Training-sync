#include <bits/stdc++.h>
using ll = long long;
using i64 = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<char>op(n);
    vector<int>c(n);
    for(int i = 0;i < n;i++){
        cin >> op[i] >> c[i];
    }
    auto sc = c;
    sort(sc.begin(),sc.end());
    sc.erase(unique(sc.begin(),sc.end()), sc.end());
    for(int i = 0;i < n;i++){
        c[i] = lower_bound(sc.begin(),sc.end(), c[i]) - sc.begin();
    }
    int m = sc.size();
    vector<int>st(m);
    
    // 0 : empty
    // 1 : T
    // 2 : F
    // 3 : insert
    vector<int>act(n);
    
    // 0 : del
    // 1 : empty 
    for(int i = n - 1;i >= 0;i--){
        if(op[i] == '+'){
            if(st[c[i]] == 0){
                act[i] = 0;
            }
            else if(st[c[i]] == 1){
                act[i] = 1;
            }
            else if(st[c[i]] == 2){
                act[i] = 0;
            }
            else if(st[c[i]] == 3){
                act[i] = 0;
            }
            st[c[i]] = 3;
        }
        else if(op[i] == 'T'){
            if(st[c[i]] == 0){
                act[i] = 0;
            }
            else if(st[c[i]] == 1){
                act[i] = 1;
            }
            else if(st[c[i]] == 2){
                act[i] = 0;
            }
            else if(st[c[i]] == 3){
                act[i] = 0;
            }
            st[c[i]] = 1;
        }
        else{
            if(st[c[i]] == 0){
                act[i] = 1;
            }
            else if(st[c[i]] == 1){
                assert(0);
            }
            else if(st[c[i]] == 2){
                act[i] = 1;
            }
            else if(st[c[i]] == 3){
                act[i] = 1;
            }
            st[c[i]] = 2;
        }
    }

    // for(int i = 0;i < n;i++){
    //     cerr << act[i] << " ";
    // }
    // cerr << endl;

    string ans;
    stack<int>stk;
    vector<int>ok(n);
    for(int i = 0;i < n;i++){
        if(op[i] == '+'){
            ans.push_back('+');
            stk.push(c[i]);
            if(act[i] == 0){
                ok[c[i]] = 1;
            }
        }
        else if(op[i] == 'T'){
            ans.push_back('?');
            if(act[i] == 0){
                ok[c[i]] = 1;
            }
        }
        else{
            ans.push_back('?');
            if(act[i] == 0){
                ok[c[i]] = 1;
            }
        }

        while(!stk.empty() && ok[stk.top()]){
            ok[stk.top()] = 0;
            stk.pop();
            ans += '-';
        }
    }
    assert(stk.empty());
    cout << ans << "\n";
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}