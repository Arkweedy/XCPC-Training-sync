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
    vector<int>x(n),y(n);
    for(int i = 0;i < n;i++){
        cin>>x[i]>>y[i];
    }
    vector<int>idx(n),idy(n);
    iota(idx.begin(),idx.end(),0);
    sort(idx.begin(),idx.end(),[&](int i,int j)->bool
    {
        return x[i] < x[j];
    });
    iota(idy.begin(),idy.end(),0);
    sort(idy.begin(),idy.end(),[&](int i,int j)->bool
    {
        return y[i] < y[j];
    });

    

    vector<int>z(n);
    for(int i = n / 2;i < n;i++){
        z[idx[i]] += 1;
        z[idy[i]] += 2;
    }
    
    array<vector<int>,4>c;
    for(int i = 0;i < n;i++){
        c[z[i]].push_back(i);
    }
   
    //ans
    for(int i = 0;i < c[0].size();i++){
        cout<<c[0][i] + 1<<" "<<c[3][i] + 1<<'\n';
    }
    for(int i = 0;i < c[1].size();i++){
        cout<<c[1][i] + 1<<" "<<c[2][i] + 1<<'\n';
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