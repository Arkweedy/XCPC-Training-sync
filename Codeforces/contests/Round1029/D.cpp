#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<ll>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }

    
    if(a[1] <= a[n]){
        ll d = a[n] - a[1];
        if(d % (n - 1) != 0){
            cout<<"No"<<endl;
            return;
        }else{
            ll c = d / (n - 1);
            a[1] -= c;
            if(a[1] % (n + 1) != 0){
                cout<<"No"<<endl;
                return;
            }
            ll x = a[1] / (n + 1);
            if(x < 0 || c < 0){
                cout<<"No"<<endl;
                return;
            }
            for(int i = 1;i <= n;i++){
                a[i] -= x * (n + 1);
            }
            for(int i = 2;i <= n;i++){
                a[i] -= i * c;
            }

            for(int i = 1;i <= n;i++){
                if(a[i] != 0){
                    cout<<"No"<<endl;
                    return;
                }
            }
            cout<<"Yes"<<endl;
            return;
        }
    }else{
        for(int i = 1;i <= n / 2;i++){
            swap(a[i],a[n - i + 1]);
        }
        ll d = a[n] - a[1];
        if(d % (n - 1) != 0){
            cout<<"No"<<endl;
            return;
        }else{
            ll c = d / (n - 1);
            a[1] -= c;
            if(a[1] % (n + 1) != 0){
                cout<<"No"<<endl;
                return;
            }
            ll x = a[1] / (n + 1);
            if(x < 0 || c < 0){
                cout<<"No"<<endl;
                return;
            }
            for(int i = 1;i <= n;i++){
                a[i] -= x * (n + 1);
            }
            for(int i = 2;i <= n;i++){
                a[i] -= i * c;
            }

            for(int i = 1;i <= n;i++){
                if(a[i] != 0){
                    cout<<"No"<<endl;
                    return;
                }
            }
            cout<<"Yes"<<endl;
            return;
        }
    }
    
    return;



    // int sq = ceil(sqrt(n));
    // int l = sq, r = n - sq;
    // auto check = [&](int x, int i)->int
    // {
    //     int j = n - i + 1;
    //     if(j < i)swap(i,j);
    //     for(int k = 0;k < i;k++){
    //         if(x % i == 0){
    //             return true;
    //         }
    //         x -= j;
    //         if(x < 0)return false;
    //     }
    //     return false;
    // };
    // int ok = 1;
    // for(int i =1;i <= n;i++){
    //     ok &= check(a[i],i);
    // }
    // if(ok){
    //     cout<<"Yes"<<endl;
    // }else{
    //     cout<<"No"<<endl;
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
    #ifdef LOCAL_DEBUG
        system("pause");
    #endif
    return 0;
}