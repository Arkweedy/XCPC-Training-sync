#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.30 20:20:45

void solve()
{
    int x, y, z;
    cin >> x >> y >> z;
    array<int,3>v = {x, y, z};
    sort(v.begin(),v.end());
    vector<int>a,b,c;
    int v1 = 1, v2 = 1;
    if(v[1] == v[0]){
        v1 = v2 = 0;
    }
    if(v[1] > v[0] * 2 && v[2] > v[0] * 2){
        for(int i = 0;i < x - 1;i++){
            a.push_back(0);
            c.push_back(0);
        }
        for(int i = 0;i < y;i++){
            a.push_back(1);
            b.push_back(1);
        }
        c.push_back(1);
        for(int i = 0;i < z - 1;i++){
            c.push_back(0);
            b.push_back(0);
        }
    }
    else{
        for(int i = 0;i < v[1] - v[0];i++){
            a.push_back(v1);
            b.push_back(v1);
        }
        for(int i = 0;i < v[0];i++){
            a.push_back(0);
            b.push_back(0);
            c.push_back(0);
        }
        for(int i = 0;i < v[2] - v[0];i++){
            b.push_back(v2);
            c.push_back(v2);
        }
    }
    vector<int>ansx,ansy,ansz;
    //ab -> v[1]
    //ac -> v[0]
    //bc -> v[2]

    // abc -> v[1] v[0] v[2]
    // now :  x, y, z to v[1] v[0] v[2] 
    // x 13
    if(x == v[0] && y == v[1] && z == v[2]){
        //x min 
        ansx = a;
        ansy = c;
        ansz = b;
    }

    if(x == v[0] && y == v[2] && z == v[1]){
        ansx = c;
        ansy = a;
        ansz = b;
    }

    if(x == v[1] && y == v[0] && z == v[2]){
        ansx = a;
        ansy = b;
        ansz = c;
    }

    if(x == v[1] && y == v[2] && z == v[0]){
        ansx = b;
        ansy = a;
        ansz = c;
    }

    if(x == v[2] && y == v[0] && z == v[1]){
        ansx = c;
        ansy = b;
        ansz = a;
    }

    if(x == v[2] && y == v[1] && z == v[0]){
        ansx = b;
        ansy = c;
        ansz = a;
    }

    

    cout << ansx.size() << " ";
    for(auto v : ansx){
        cout << v << " ";
    }
    cout << "\n";

    cout << ansy.size() << " ";
    for(auto v : ansy){
        cout << v << " ";
    }
    cout << "\n";

    cout << ansz.size() << " ";
    for(auto v : ansz){
        cout << v << " ";
    }
    cout << "\n";
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}