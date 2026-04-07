#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;

using namespace std;
int K =5;
constexpr int N =6;
int a[N][N];
int check(){
    if(!a[3][3]) return 0;
    int n=K;
    int o=0;
    for(int i=1;i<=n;i++){
        o=0;
        for(int j=1;j<=n;j++) o^=a[i][j];
        if(o) return 0;
    }
    for(int j=1;j<=n;j++)
        {
            int o=0;
            for(int i=1;i<=n;i++) o^=a[i][j];
            if(o) return 0;
        }
    o=0;
    for(int i=1;i<=n;i++) o^=a[i][i];
    if(o) return 0;
    o=0;
    for(int i=1;i<=n;i++) o^=a[i][n+1-i];
    if(o) return 0;
    return 1;
}
void print(){
    int s=0;

    for(int i=1;i<=K;i++)
        {
            for(int j=1;j<=K;j++) cout<<a[i][j]<<' ',s+=a[i][j];
            cout<<endl;
        }
    cout<<s<<endl;
    cout<<endl;
}
int cnt=0;
void dfs(int x,int y)
{   
    if(x>K){
        if(check()) print();
        return ;
    }
    for(int i=0;i<2;i++) {
        a[x][y]=i;
        int xx=x,yy=y+1;
        if(yy>K) yy=1,xx=x+1;
        dfs(xx,yy);
    }
}
void solve()
{ 
    dfs(1,1);

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
   // cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}