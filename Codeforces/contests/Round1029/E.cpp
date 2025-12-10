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
    vector<int>a(n),b(n);
    map<int,int>lmp,rmp;
    map<int,int>lmp2,rmp2;
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
    }
    
    int rpos = -1;
    
    for(int i = 0;i < n;i++){
        int x,y;
        if(i % 2 == 0){
            x = a[i],y = b[i];
        }else{
            x = b[i],y = a[i];
        }
        lmp[x] = i;
        rmp[y] = i;

        if(i >= 1){
            //op
            if(lmp2.count(x)){
                rpos = max(rpos, lmp2[x]);
            }
            if(rmp2.count(y)){
                rpos = max(rpos, rmp2[y]);
            }
            //lazy upt
            int nx ,ny;
            if(i % 2 == 1){
                nx = a[i - 1],ny = b[i - 1];
            }else{
                nx = b[i - 1],ny = a[i - 1];
            }
            lmp2[nx] = i - 1;
            rmp2[ny] = i - 1;
        }
    }
    //not op
    for(auto [v,p] : lmp){
        if(rmp.count(v)){
            rpos = max(rpos, min(p, rmp[v]));
        }
    }
    //cerr<<lmp[2]<<" "<<rmp[2]<<endl;

    cout<<rpos + 1<<endl;
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