#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//G.cpp Create time : 2026.02.21 18:47

void solve()
{
    int n;
    cin >> n;
    int sum = 1, cnt = 1, chs = 0;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    int ok = 1;
    for(int i = 0;i < n;i++){
        if(a[i] == 0){
            if(cnt > 1){
                chs++;
                cnt--;
            }
            else{
                sum++;
                cnt++;
            }
        }
        else if(a[i] == 1){
            sum++;
            cnt++;
        }
        else if(a[i] == -1){
            if(cnt > 1){
                cnt--;
            }
            else if(chs > 0){
                chs--;
                sum++;
                cnt++;
            }
            else{
                ok = 0;
                break;
            }
        }
    }
    if(!ok){
        cout << -1 << endl;
    }
    else{
        //chs and cnt
        int g = gcd(sum, cnt);
        sum /= g;
        cnt /= g;
        cout << sum << " " << cnt << endl;
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