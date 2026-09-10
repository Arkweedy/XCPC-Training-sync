#include<bits/stdc++.h>
#define N 30
using i64 = long long;
using ll = long long;

using namespace std;

struct node{int x,y,c;};
bool operator <(node a,node b){
    if(a.x!=b.x) return a.x<b.x;
    return a.y<b.y;
}
set<node> e[N][N];
void add(int x,int y,int xx,int yy,int c){e[x][y].insert({xx,yy,c});}
vector<int> ans;
void dfs(int x,int y,int c){
    while(e[x][y].size()){
        auto [xx,yy,cc]=*e[x][y].begin();
        e[x][y].erase(node{xx,yy,cc});
        int ccc=cc;
        if(ccc<3) ccc+=3;
        else ccc-=3;
        e[xx][yy].erase(node{x,y,ccc});
        dfs(xx,yy,cc);
    }
    if(c>=0) ans.push_back(c);
}
void solve()
{
    int n;cin>>n;
    n++;
    for(int i=1;i<n;i++)
        for(int j=1;j<=i;j++){

            add(i,j,i+1,j,4);add(i+1,j,i,j,1);
            add(i,j,i+1,j+1,5);add(i+1,j+1,i,j,2);
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++){
            add(i,j,i,j+1,0);add(i,j+1,i,j,3);
        }
    dfs(1,1,-1);
    assert(ans.size()==3*n*(n-1)/2);
    while(ans.size()) cout<<ans.back(),ans.pop_back();
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
