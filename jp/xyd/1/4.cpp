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
    vector<set<int>>s(10);
    while(n--){
        int op;
        cin>>op;
        if(op == 1){
            int x,y;
            cin>>x>>y;
            s[x].insert(y);
        }
        else if(op == 2){
            int x,y;
            cin>>x>>y;
            s[x].erase(y);
        }
        else if(op == 3){
            int x,y;
            cin>>x>>y;
            for(auto e : s[y])s[x].insert(e);
            s[y].clear();
        }
        else if(op == 4){
            int x,y;
            cin>>x>>y;
            vector<int>buf;
            for(auto e : s[x]){
                if(!s[y].count(e)){
                    buf.push_back(e);
                }
            }
            s[y].clear();
            for(auto e : buf)s[x].erase(e);
        }
        else if(op == 5){
            int x,y;
            cin>>x>>y;
            if(s[x].count(y)){
                cout<<"Yes"<<endl;
            }
            else{
                cout<<"No"<<endl;
            }
        }
        else{
            int x;
            cin>>x;
            cout<<s[x].size()<<endl;
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