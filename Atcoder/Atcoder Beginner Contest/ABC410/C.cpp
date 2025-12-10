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
    vector<int>a(n);
    iota(a.begin(),a.end(),1);
    int head = 0;
    while(q--){
        int op ;
        cin>>op;
        if(op == 1){
            int p, x;
            cin>>p >> x;
            p--;
            int pos = (p + head) % n;
            a[pos] = x;
        }else if(op == 2){
            int p;
            cin>>p;
            p--;
            int pos = (p + head) % n;
            cout<<a[pos]<<"\n";
        }else{
            int k;
            cin>>k;
            head+=k;
            head %= n;
        }
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