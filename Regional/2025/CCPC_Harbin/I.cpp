#include<bits/stdc++.h>

using ll = long long;
using namespace std;

using Node = array<int,2>;

int dx[] = {1,1,0,0,-1,-1};
int dy[] = {-1,0,1,-1,1,0};

const int M = 4;
void solve()
{
    vector<Node>c;
    for(int i=0;i<M*M;i++){
        int x = i%M;
        int y = i/M % M;
        c.push_back({x,y});
    }

    set<set<Node>>s;
    s.insert(set<Node>());

    queue<set<Node>>q;
    q.push(set<Node>());
    while(!q.empty()){
        auto u = q.front();
        q.pop();
        for(auto [x,y]:c){
            auto ns = u;
            bool flg = 1;
            for(int i=0;i<6;i++){
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx >=M || ny >= M || nx < 0 || ny < 0)flg = 0;
                if(ns.count({nx,ny})){
                    ns.erase({nx,ny});
                }else{
                    ns.insert({nx,ny});
                }
            }
            if(!s.count(ns) && flg){
                s.insert(ns);
                q.push(ns);
            }
        }
    }


    for(auto t:s){
        if(t.size() != 6)continue;
        cout<<"size: "<<t.size()<<endl;
        for(auto [x,y]:t)cout<<x<<' '<<y<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}