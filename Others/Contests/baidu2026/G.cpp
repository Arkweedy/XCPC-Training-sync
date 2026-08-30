#include<bits/stdc++.h>

using i64 = long long;

using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    int sum = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        if(a[i] != -1)sum += a[i];
    }

    int rem = n - sum;
    auto check = [&](int p)->bool
    {
        if(a[p] == -1){//others : 0
            for(int i = 0;i < n;i++){
                if(a[i] >= rem)return false;
            }
            return true;
        }
        else{
            int m = rem;
            for(int i = 0;i < n;i++){
                if(i == p)continue;
                if(a[i] != -1){
                    if(a[i] >= a[p])return false;
                }
                else{
                    m -= a[p] - 1;
                }
            }
            if(m > 0)return false;
            return true;
        }
    };

    for(int i = 0;i < n;i++){
        if(check(i)){
            cout << i + 1 << " ";
        }
    }
    cout << endl;

    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}