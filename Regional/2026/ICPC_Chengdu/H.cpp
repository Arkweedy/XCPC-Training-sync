#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
 
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int>a,b;
    auto ask = [&](int i, int j)->int
    { 
        cout << "? " << i << " " << j << endl;
        int res;
        cin >> res;
        return res;
    };

    int p = 1;
    for(int i = 2;i <= n;i++){
        int x = ask(p, i);
        if(x)b.push_back(i);
        else {
            a.push_back(p);
            p = i;
        }
    }
    a.push_back(p);

    if(b.empty()){
        cout << "! ";
        for(auto x : a){
            cout << x << " ";
        }
        cout << endl;
        return;
    }

    int q = b[0];
    vector<int>b0, b1;
    for(int i = 1;i < b.size();i++){
        int x = ask(q, b[i]);
        if(x){
            b0.push_back(b[i]);
        }
        else{
            b1.push_back(q);
            q = b[i];
        }
    }
    b1.push_back(q);

    int bma = b1.back();

    int pos = -1;
    for(int i = 0;i < a.size() - 1;i++){
        int x = ask(bma, a[i]);
        if(x)continue;
        else {
            pos = i;
            break;
        }
    }
    if(pos == -1)pos = a.size() - 1;

    vector<int>ans;
    for(int i = 0;i < pos;i++){
        ans.push_back(a[i]);
    }
    for(auto x : b0){
        ans.push_back(x);
    }
    for(auto x : b1){
        ans.push_back(x);
    }
    for(int i = pos;i < a.size();i++){
        ans.push_back(a[i]);
    }

    cout << "! ";
    for(auto x : ans){
        cout << x << " ";
    }
    cout << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}