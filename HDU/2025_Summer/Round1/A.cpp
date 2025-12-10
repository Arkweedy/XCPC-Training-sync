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
    vector<int>flg(n),sg(n),asg(n);
    for(int i = 0;i < n;i++){
        int k;
        cin>>k;
        for(int j = 0;j < k;j++){
            int x;
            cin>>x;
            sg[i]^=x;
            if(x > 1)flg[i] = 1;
        }
        if(sg[i] && flg[i]){
            asg[i] = 1;
        }
        else if(!sg[i] && !flg[i]){
            asg[i] = 1;
        }
    }

    for(int i = 0;i < n;i++){
        cerr<<sg[i]<<" ";
    }
    cerr<<endl;
     for(int i = 0;i < n;i++){
        cerr<<asg[i]<<" ";
    }
    cerr<<endl;

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