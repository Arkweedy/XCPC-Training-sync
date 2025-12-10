#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int lowbit(int x)
{
    return x & -x;
}

int highbit(int x)
{
    while(x != lowbit(x)){
        x -= lowbit(x);
    }
    return x;
}

int bits(int x)
{
    int res = 0;
    while(x != 0){
        x >>= 1;
        res++;
    }
    return res;
}


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n + 1), b(n + 1);
    for(int i = 1;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
    }
    vector<int>c(n + 1);
    for(int i = 0;i < n;i++){
        c[i] = a[i] | a[i + 1];
    }
    cerr<<endl;
    for(int i = 1;i < n;i++){
        if((c[i - 1] & c[i]) != a[i]){
            cout<<-1<<endl;
            return;
        }
    }

    vector<int>k(n);
    for(int i = 0;i < n;i++){
        if(b[i] <= c[i]){
            k[i] = -1;
        }
        else{
            k[i] = bits(b[i]);
        }
    }

    vector<ll>cost(n), more(n);
    for(int i = 0;i < n;i++){
        if(k[i] == -1){
            cost[i] = c[i] - b[i];
            more[i] = 0;
        }
        else{
            int x = b;
            while(x & c[i] != c[i]){
                c[i]++
            }
            cost[i] = highbit(b[i]) * 2ll - b[i] + c[i];
            more[i] = highbit(b[i]) * 2ll;
        }
    }

    for(int i = 0;i < n;i++){
        cerr<<b[i]<<" ";
    }
    cerr<<endl;

    for(int i = 0;i < n;i++){
        cerr<<c[i]<<" ";
    }
    cerr<<endl;

    for(int i = 0;i < n;i++){
        cerr<<cost[i]<<" ";
    }
    cerr<<endl;

    for(int i = 0;i < n;i++){
        cerr<<more[i]<<" ";
    }
    cerr<<endl;

    constexpr ll inf = 114514191981011;
    vector<array<ll,2>>dp(n + 1, {inf,inf});//0 : self , 1 : +1
    dp[0] = {0,0};
    for(int i = 0;i < n;i++){
        if(i == 0){
            dp[i + 1][0] = cost[i];
            dp[i + 1][1] = cost[i] + more[i];
        }
        else{
            if(k[i] == k[i + 1]){
                dp[i + 1][0] = dp[i][1] + cost[i];
                dp[i + 1][1] = dp[i][0] + cost[i] + more[i];
            }else if(k[i] == k[i + 1] + 1){
                dp[i + 1][0] = min(dp[i][0], dp[i][1]) + cost[i];
                dp[i + 1][1] = dp[i][1] + cost[i] + more[i];
            }else if(k[i] + 1 == k[i + 1]){
                dp[i + 1][0] = dp[i][0]+ cost[i];
                dp[i + 1][1] = min(dp[i][0], dp[i][1])  + cost[i] + more[i];
            }else{
                dp[i + 1][0] = min(dp[i][0], dp[i][1]) + cost[i];
                dp[i + 1][1] = min(dp[i][0], dp[i][1])  + cost[i] + more[i];
            }
        }
    }
    cout<<min(dp[n][0],dp[n][1])<<endl;
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