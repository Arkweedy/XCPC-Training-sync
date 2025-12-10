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
    map<string,int>mp;
    while(n--){
        int op;
        cin>>op;
        if(op == 1){
            string s;
            int x;
            cin>>s>>x;
            mp[s] = x;
        }
        else{
            string s;
            cin>>s;
            if(!mp.count(s)){
                cout<<"Not found."<<endl;
            }
            else{
                cout<<mp[s]<<endl;
            }
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