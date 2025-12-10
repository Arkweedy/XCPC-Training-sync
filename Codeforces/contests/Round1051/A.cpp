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
    vector<int>a(n);
    vector<int>pos(n + 1);
    for(int i = 0;i < n;i++){
        cin>>a[i];
        pos[a[i]] = i;
    }

    int l = pos[n], r = pos[n];
    for(int i = n;i >= 1;i--){
        if(pos[i] != l && pos[i] != r){
            cout<<"No"<<endl;
            return;
        }
        if(pos[i] == l){
            l--;
        }
        if(pos[i] == r){
            r++;
        }
    }
    cout<<"Yes"<<endl;
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