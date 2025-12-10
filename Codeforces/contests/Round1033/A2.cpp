#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    vector<pair<int,int>>a(3);
    for(int i = 0;i < 3;i++){
        cin>>a[i].first>>a[i].second;
    }
    sort(a.begin(),a.end());
    if(a[0].first == a[2].first){
        if(a[0].first == a[0].second + a[1].second + a[2].second){
            cout<<"Yes"<<endl;
            return;
        }
    }else{
        if(a[0].first == a[1].first && a[0].second + a[1].second == a[2].second){
            if(a[0].first + a[2].first == a[2].second){
                cout<<"Yes"<<endl;
                return;
            }
        }
    }
    for(int i = 0;i < 3;i++){
        swap(a[i].first,a[i].second);
    }
    sort(a.begin(),a.end());
    if(a[0].first == a[2].first){
        if(a[0].first == a[0].second + a[1].second + a[2].second){
            cout<<"Yes"<<endl;
            return;
        }
    }else{
        if(a[0].first == a[1].first && a[0].second + a[1].second == a[2].second){
            if(a[0].first + a[2].first == a[2].second){
                cout<<"Yes"<<endl;
                return;
            }
        }
    }
    cout<<"No"<<endl;
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