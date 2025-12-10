#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.30 11:05:59

void solve()
{
    ll n;
    cin>>n;
    vector<int>a;
    while(n){
        a.push_back(n % 10);
        n /= 10;
    }

    int p = 1;
    //check 1
    int ok1 = 1;
    for(auto x : a){
        if(x >= p && x <= p * 3)continue;
        else if(x < p)p = x;
        else ok1 = 0;
    }
    if(ok1){
        cout<<1<<endl;
        return;
    }

    int ok2 = 1;
    p = 2;
    for(auto x : a){
        if(x >= p && x <= p * 3)continue;
        else if(x < p)p = x;
        else ok2 = 0;
    }
    if(ok2){
        cout<<2<<endl;
        return;
    }

    int ok3 = 1;
    p = 3;
    for(auto x : a){
        if(x >= p && x <= p * 3)continue;
        else if(x < p)p = x;
        else ok3 = 0;
    }
    if(ok3){
        cout<<3<<endl;
        return;
    }

    //1033 -> 5
    //check 4
    int ok4 = 1;
    int carry = 0;
    p = 4;
    for(auto x : a){
        if(p == 4){
            if(!carry){
                if(x <= 2){
                    carry = 1;
                }
                else if(x >= 4){
                    carry = 0;
                }
                else{
                    p = 3;
                    //ok4 = 0;
                }
            }
            else{
                if(x <= 3){
                    carry = 1;
                }
                else if(x >= 5){
                    carry = 0;
                }
                else{
                    p = 3;
                    //ok4 = 0;
                }
            }
        }
        else{
            if(x >= p && x <= p * 3)continue;
            else if(x < p)p = x;
            else ok4 = 0;
        }
    }
    if(ok4){
        cout<<4<<endl;
        return;
    }

    cout<<5<<endl;
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