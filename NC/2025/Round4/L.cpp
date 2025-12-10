#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    
    vector<int>e(n + 1);//
    for(int i = 1;i <= n;i++){
        e[i] = (e[i - 1] + a[i] + 1) / 2;
    }

    vector<int>e1(n + 1);
    for(int i = 1;i <= n;i++){
        e1[i] = (e[i - 1] + a[i] + 2) / 2;
    }

    vector<int>same(n + 1);//pass a[i] 
    for(int i = 1;i <= n;i++){
        same[i] = (e1[i] == e[i]);
    }

    vector<int>r(n + 1);//
    int p = n + 1;
    for(int i = n;i >= 1;i--){
        if(same[i]){
            p = i - 1;
        }
        r[i] = p;
    }

    auto calc = [&](int pos, int x)->int
    {
        int p = upper_bound(a.begin(),a.end(),x)-a.begin(); 
        if(p > pos)return x;

        while(p <= pos && x > e[p - 1] + 1){
            x = (x + a[p] + 1) / 2;
            p++;
        }
        if(p > pos)return x;
        if(x == e[p - 1])return e[pos];
        else if(x == e[p - 1] + 1 && r[p] >= pos)return e[pos] + 1;
        else return e[pos];
    };

    while(q--){
        int x,y;
        cin>>x>>y;
        y = n + 1 - y;
        cout<<calc(y,x) - x<<endl;
    }
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