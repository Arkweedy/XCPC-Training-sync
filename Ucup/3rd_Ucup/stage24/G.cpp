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
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }

    auto ok = [&](int x, int y)->bool
    {
        return x >= 0 && y >= 0 && x < n && y < n;
    };

    vector<int>dx = {1,1,1,0,0,-1,-1,-1},dy = {1,0,-1,1,-1,1,0,-1};
    auto find = [&](int x,int y, char c)->bool
    {
        for(int i = 0;i < 8;i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(ok(nx,ny)){
                if(a[nx][ny] == c){
                    return true;
                }
            }
        }
        return false;
    };

    auto get_score = [&](int x,int y, char c)->int
    {
        int res = 0;
        for(int i = 0;i < 8;i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(ok(nx,ny)){
                if(a[nx][ny] == c){
                    res++;
                }
            }
        }
        return res;
    };

    auto nobuild = [&](char c)->bool
    {
        return c == 'o' || c == 'm' || c == 'p'; 
    };

    int ans = 0;
    int score = 0;
    int cnt = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(a[i][j] == 'O'){
                ans += get_score(i,j,'O');
                cnt++;
            }
            if(a[i][j] == 'P'){
                ans += get_score(i,j,'M');
                cnt++;
            }
            if(a[i][j] == 'M'){
                ans += get_score(i,j,'P');
                cnt++;
            }
        }
    }
    ans /= 2;
    ans += cnt;
    cnt = 0;



    while(1){
        int flg = 0;
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(a[i][j] == 'o'){
                    if(find(i,j,'O')){
                        a[i][j] = 'O';
                        flg = 1;
                    }
                }
                if(a[i][j] == 'p'){
                    if(find(i,j,'M')){
                        a[i][j] = 'P';
                        flg = 1;
                    }
                }
                if(a[i][j] == 'm'){
                    if(find(i,j,'P')){
                        a[i][j] = 'M';
                        flg = 1;
                    }
                }
            }
        }
        if(!flg)break;
        
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(a[i][j] == 'O'){
                score += get_score(i,j,'O');
                cnt++;
            }
            if(a[i][j] == 'P'){
                score += get_score(i,j,'M');
                cnt++;
            }
            if(a[i][j] == 'M'){
                score += get_score(i,j,'P');
                cnt++;
            }
        }
    }
    score /= 2;
    score += cnt;

    cout<<ans<<" "<<score<<endl;
    for(int i = 0;i < n;i++){
        cout<<a[i]<<endl;
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