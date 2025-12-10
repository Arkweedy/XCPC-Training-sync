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

    auto ask = [&](int p, vector<int>a)->int
    {
        cout<<"? ";
        cout<<p<<" ";
        cout<<a.size()<<" ";
        for(int i = 0;i < a.size();i++){
            cout<<a[i]<<" ";
        }
        cout<<endl;
        int res;
        cin>>res;
        return res;
    };

    vector<vector<int>>layer(n + 1);
    vector<int>all(n);
    int maxdep = 0;
    iota(all.begin(),all.end(),1);
    for(int i = 1;i <= n;i++){
        int dep = ask(i, all);
        layer[dep].push_back(i);
        maxdep = max(maxdep, dep);
    }
    //layer begin form 1
    vector<int>slack(maxdep + 1);

    for(int i = maxdep;i >= 1;i--){
        for(auto p : layer[i]){
            vector<int>points;
            for(int j = i + 1;j <= maxdep;j++){
                points.push_back(slack[j]);
            }
            points.push_back(p);
            for(int j = i - 1;j >= 1;j--){
                for(auto s : layer[j]){
                    points.push_back(s);
                }
            }
            int bg = p;
            if(i != maxdep)bg = slack[maxdep];
            int res = ask(bg, points);
            //cerr<<"# dep = "<<i<<" new dep = "<<res<<endl;
            if(res == maxdep){
                slack[i] = p;
                break;
            }
        }
    }

    //ans
    cout<<"! "<<maxdep<<" ";
    for(int i = maxdep;i >= 1;i--){
        cout<<slack[i]<<" ";
    }
    cout<<endl;
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