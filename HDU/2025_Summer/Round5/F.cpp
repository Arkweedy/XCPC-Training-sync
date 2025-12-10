#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

map<vector<int>,int>mp1;
map<vector<int>,int>mp2;
constexpr int N = 300;

int sg1(vector<int>a)
{
    if(count(a.begin(),a.end(),1) == a.size()){
        return 0;
    }
    else if(mp1.count(a)){
        return mp1[a];
    }
    else{
        vector<int>mex(N);
        int n = a.size();
        for(int i = 0;i < n;i++){
            if(i == 0){
                if(a[i] == 0 || a[i + 1] == 0){
                    auto b = a;
                    b[i] = b[i + 1] = 1;
                    mex[sg1(b)] = 1;
                }
            }
            else if(i == n - 1){
                if(a[i] == 0 || a[i - 1] == 0){
                    auto b = a;
                    b[i] = b[i - 1] = 1;
                    mex[sg1(b)] = 1;
                }
            }
            else{
                if(a[i] == 0 || a[i - 1] == 0 || a[i + 1] == 0){
                    auto b = a;
                    b[i + 1] = b[i] = b[i - 1] = 1;
                    mex[sg1(b)] = 1;
                }
            }
        }
        for(int i = 0;i < N;i++){
            if(mex[i] == 0){
                mp1[a] = i;
                return i;
            }
        }
    }
}

int sg2(vector<int>a)
{
    if(count(a.begin(),a.end(),1) == a.size()){
        return 0;
    }
    else if(mp2.count(a)){
        return mp2[a];
    }
    else{
        vector<int>mex(N);
        int n = a.size();
        for(int i = 0;i < n;i++){
            if(a[i] == 0 || a[(i - 1 + n) % n] == 0 || a[(i + 1) % n] == 0){
                auto b = a;
                b[(i + 1) % n] = b[i] = b[(i - 1 + n) % n ] = 1;
                mex[sg2(b)] = 1;
            }
        }
        for(int i = 0;i < N;i++){
            if(mex[i] == 0){
                mp1[a] = i;
                return i;
            }
        }
    }
}

void solve()
{
    int n;
    cin>>n;
    int sg = 0;
    vector<int>sg1 = {0,1,1,3},sg2 = {0,0,0,1};
    vector<int>msg1 = {114514,1,1,2},msg2 = {114514,1,1,1};
    for(int i = 0;i < n;i++){
        ll x,tp;
        cin>>x>>tp;
        if(tp == 1){
            if(x <= 3){
                sg ^= msg1[x];
            }
            else{
                sg ^= sg1[x % 4];
            }
        }
        else if(tp == 0){
            if(x <= 3){
                sg ^= msg2[x];
            }
            else{
                sg ^= sg2[x % 4];
            }
        }
    }
    //cerr<<sg<<endl;
    if(sg != 0){
        cout<<"Yes"<<endl;
    }
    else{
        cout<<"No"<<endl;
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