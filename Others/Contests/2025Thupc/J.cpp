#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.14 12:36:38

ll lowbit(ll x)
{
    return x & -x;
}

ll highbit(ll x)
{
    while(x != lowbit(x)){
        x -= lowbit(x);
    }
    return x;
}

ll digit(ll x)
{
    int res = 0;
    while(x != 1){
        x /= 2;
        res++;
    }
    return res;
}

void solve()
{
    ll n ,m;
    cin >> n >> m;
    ll x = m;
    if(n % 2 == 0){
        cout << "NO" << "\n";
    }
    else if(n == 1){
        cout <<"NO" <<"\n";
    }
    else{
        if(x == lowbit(x)){
            if(digit(x) % 2 == 0){
                cout <<"YES" <<"\n";
            }
            else{
                cout <<"NO" <<"\n";
            }
        }
        else{
            int cnt = 0;
            while(x != lowbit(x)){
                x = highbit(x) * 2 - x;
                cnt++;
                //cerr << x << endl;
            }
            if(cnt * 2 + 1 <= n && digit(x) % 2 == 0){
                cout <<"YES" << "\n";
            }
            else{
                cout << "NO" << "\n";
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
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}