#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int x,n;
    
    while(cin>>x>>n){
        priority_queue<ll,vector<ll>,greater<ll>>q;
        set<ll>s;
        s.insert(x);
        q.push(x);
        while(1){
            ll p = q.top();
            q.pop();
            if(!s.count(p * 2 + 1)){
                q.push(p * 2 + 1);
                s.insert(p * 2 + 1);
            }
            if(!s.count(p * 3 + 1)){
                q.push(p * 3 + 1);
                s.insert(p * 3 + 1);
            }

            if(s.size() >= n * 2 + 20){
                break;
            }
        }

        int tot = 0;
        for(auto x : s){
            tot++;
            if(tot == n){
                cout<<x<<endl;
            }
        }
    }
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