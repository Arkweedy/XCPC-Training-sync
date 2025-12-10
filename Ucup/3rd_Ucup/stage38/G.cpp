#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 1e9 + 7;

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    int c = n - count(a.begin(),a.end(), 1);
    int l = 0, r = n - 1;
    int limit = __lg(n) + 2;
    int upper = n * 3;
    while(l < n && a[l] == 1)l++;
    while(r >= l && a[r] == 1)r--;
    int ps = l + n - r - 1;
    
    //vector<int>err(x);
    if(c > limit){
        
        ll ans = 1;
        for(int i = l;i <= r;i++){
            ans = ans * a[i] % P;
        }
        ans = (ans + ps) % P;
        cout<<ans<<endl;
        return;
    }
    else{
        vector<int>b(c),d(c);
        int mid = 0;
        int tot = 0;
        for(int i = l;i <= r;i++){
            if(a[i] == 1){
                mid++;
            }
            else{
                b[tot] = a[i];
                d[tot] = mid;
                tot++;
                mid = 0;
            }
        }

        ll ans = 1;
        int flg = 0;
        for(int i = 0;i < c;i++){
            ans = ans * b[i];
            if(ans > upper){
                flg = 1;
                break;
            }
        }

        if(flg){
            ans = 1;
            for(int i = 0;i < c;i++){
                ans = ans * b[i] % P;
            }
            ans = (ans + ps) % P;
            cout<<ans<<endl;
            return;
        }

        //
        ans = 0;
        int len = 1 << c - 1;
        for(int i = 0;i < len;i++){
            ll sum = 0;
            ll now = b[0];
            for(int j = 0;j < c - 1;j++){
                if(i >> j & 1){
                    now = now * b[j + 1];
                }
                else{
                    sum += now;
                    sum += d[j + 1];
                    now = b[j + 1];
                }
            }
            sum += now;
            //cerr<<"sum = "<<sum<<endl;
            ans = max(ans, sum);
        }
        ans += ps;
        ans %= P;
        cout<<ans<<endl;
        return;
    }
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