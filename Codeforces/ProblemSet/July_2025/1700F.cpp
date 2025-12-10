#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

// Wrong at all!!!!

void solve()
{
    int n;
    cin>>n;
    vector<array<int,2>>a(n),b(n);
    vector<array<int,2>>a1,b1;
    int x = 0, y = 0;
    for(int i = 0;i < n;i++){
        cin>>a[i][0];
        x += a[i][0];
        if(a[i][0] == 1){
            a1.push_back({i,0});
        }
    }
    for(int i = 0;i < n;i++){
        cin>>a[i][1];
        x += a[i][1];
        if(a[i][1] == 1){
            a1.push_back({i,1});
        }
    }
    for(int i = 0;i < n;i++){
        cin>>b[i][0];
        y += b[i][0];
        if(b[i][0] == 1){
            b1.push_back({i,0});
        }
    }
    for(int i = 0;i < n;i++){
        cin>>b[i][1];
        y += b[i][1];
        if(b[i][1] == 1){
            b1.push_back({i,1});
        }
    }
    
    if(x != y){
        cout<<-1<<endl;
        return;
    }

    ll ans = 0;
    sort(a1.begin(),a1.end());
    sort(b1.begin(),b1.end());
    vector<int>endy(x);

    for(int i = 0;i < x;i++){
        ans += abs(a1[i][0] - b1[i][0]) + abs(a1[i][1] - b1[i][1]);
        endy[i] = b1[i][1];
    }
    cout<<ans<<endl;

    constexpr int inf = 114514;
    vector<array<int,2>>dp(x,{-inf,-inf});//endy = 0 , endy = 1
    dp[0][endy[0]] = 0;
    for(int i = 1;i < x;i++){
        //00->00 10 -> 
        if(a1[i - 1][1] == 0 && a1[i][1] == 0){
            if(endy[i] == 0){//00 ->00 00->10(swaped 01)
                //same
                dp[i][0] = max(dp[i][0], max(dp[i - 1][0],dp[i - 1][1]));
                dp[i][1] = max(dp[i][1], dp[i - 1][1]);
            }
            else{//00 -> 01(swaped 10,same) 00->11
                dp[i][1] = max(dp[i][1], max(dp[i - 1][0],dp[i - 1][1]));
                dp[i][0] = max(dp[i][0], dp[i - 1][1]);//swap it
            }
        }
        else if(a1[i - 1][1] == 0 && a1[i][1] == 1){
            if(endy[i] == 0){//01 ->00 01->10(swaped 01,01->01 +2)
                //same
                dp[i][0] = max(dp[i][0], max(dp[i - 1][0],dp[i - 1][1]));
                dp[i][1] = max(dp[i][1], dp[i - 1][1] + 2);
            }
            else{//01 -> 01(swaped 10,-2) 00->11
                dp[i][1] = max(dp[i][1], max(dp[i - 1][0],dp[i - 1][1]));
                dp[i][0] = max(dp[i][0], dp[i - 1][1] - 2);//
            }
        }
        else if(a1[i - 1][1] == 1 && a1[i][1] == 0){
            if(endy[i] == 0){//10 ->00 10->10(swaped 01, - 2)
                //same
                dp[i][0] = max(dp[i][0], max(dp[i - 1][0],dp[i - 1][1]));
                dp[i][1] = max(dp[i][1], dp[i - 1][1] - 2);
            }
            else{//10 -> 01(swaped 10, +2) 10->11
                dp[i][1] = max(dp[i][1], max(dp[i - 1][0],dp[i - 1][1]));
                dp[i][0] = max(dp[i][0], dp[i - 1][1] + 2);//swap it, -2
            }
        }
        else if(a1[i - 1][1] == 1 && a1[i][1] == 1){
            if(endy[i] == 0){//11 ->00 11->10(swaped 01)
                //same
                dp[i][0] = max(dp[i][0], dp[i - 1][0]);
                dp[i][1] = max(dp[i][1], max(dp[i - 1][1],dp[i - 1][1]));
            }
            else{//11 -> 01(swaped 10,same) 11->11
                dp[i][1] = max(dp[i][1], max(dp[i - 1][0],dp[i - 1][1]));
                dp[i][0] = max(dp[i][0], dp[i - 1][0]);//swap it, -2
            }
        }

    }

    for(int i = 0;i < x;i++){
        cerr<<dp[i][0]<<" "<<dp[i][1]<<endl;
    }

    int more = max(dp[x - 1][0],dp[x - 1][1]);
    cout<<ans - more<<endl;
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