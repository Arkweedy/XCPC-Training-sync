#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.28 14:18:23

void solve()
{
    int n;
    cin>>n;
    vector<ll>a(n),b(n),c(n),d(n);
    for(int i = 1;i <= n - 2;i++){
        cin>>a[i];
    }
    for(int i = 1;i <= n - 2;i++){
        cin>>b[i];
    }
    for(int i = 1;i <= n - 2;i++){
        cin>>c[i];
    }
    for(int i = 1;i <= n - 2;i++){
        cin>>d[i];
    }

    constexpr int N = 28;
    //AABB...
    vector<array<int,4>>tr(N);//A,B,AB,BA
    //0 " " -> A, B
    //1 A->AA+,AB
    //2 B->BA,BB+
    //3 AA->AAB
    //4 AB->ABA,ABB
    //5 BA->BAA,BAB
    //6 BB->BBA
    //7 AAB 
    //8 ABA
    //9 ABB
    //10 BAA
    //11 BAB
    //12 BBA
    //13 AABB ...
    //18 BBAA 

    //19
    //AA|BB
    //BB|AA

    //19 AA+ -> ABA
    //20 BB+ -> BAB

    tr[0] = {1,2,4,5};

    tr[1] = {19,4,7,8};
    tr[2] = {5,20,11,12};

    tr[3] = {21,7,22,22}; 
    tr[4] = {8, 9,14,15};
    tr[5] = {10,11,16,17};
    tr[6] = {12,24,25,25};

    tr[7] = {22,13,23,23};
    tr[8] = {22,14,23,23};
    tr[9] = {15,25,26,26};
    tr[10] = {22,16,23,23};
    tr[11] = {17,25,26,26};
    tr[12] = {18,25,26,26};

    tr[13] = {23,26,27,27};
    tr[14] = {23,26,27,27};
    tr[15] = {23,26,27,27};
    tr[16] = {23,26,27,27};
    tr[17] = {23,26,27,27};
    tr[18] = {23,26,27,27};

    tr[19] = {21,8,22,22};
    tr[20] = {11,24,25,25};

    //op5?
    //3A 21
    //3A1B 22
    //3A2B 23
    //3B 24
    //3B1A 25
    //3B2A 26
    //3B3A && 3A3B 27
    tr[21] = {-1,22,-1,-1};
    tr[22] = {-1,23,-1,-1};
    tr[23] = {-1,27,-1,-1};
    tr[24] = {25,-1,-1,-1};
    tr[25] = {26,-1,-1,-1};
    tr[26] = {27,-1,-1,-1};
    tr[27] = {-1,-1,-1,-1};

    constexpr ll inf = 1e15;
    auto calc = [&](vector<ll>&a, vector<ll>&b)->array<ll,N>
    {
        vector<array<ll,N>>dp(n - 1,array<ll,N>{});
        dp[0].fill(inf);
        dp[0][0] = 0;
        for(int i = 1;i < n - 1;i++){
            dp[i] = dp[i - 1];
            dp[i][3] = min(dp[i][3],dp[i][19]);
            dp[i][6] = min(dp[i][6],dp[i][20]);
            dp[i][19] = dp[i][20] = inf;
            for(int j = 0;j < 4;j++){
                ll val = 0;
                if(j != 1)val += a[i];
                if(j != 0)val += b[i];
                for(int k = 0;k < N;k++){
                    if(tr[k][j] != -1){
                        //cerr<<i<<" " <<j<<" "<< k<<" "<<tr[k][j]<<" "<<dp[i][tr[k][j]]<<endl;
                        dp[i][tr[k][j]] = min(dp[i][tr[k][j]], dp[i - 1][k] + val);
                    }
                }
                
            }
            // for(int j = 21;j < N;j++){
            //     cerr<<dp[i][j]<<" ";
            // }
            // cerr<<endl;
        }
        
        return dp[n - 2];
    };
    
    auto f = calc(a, b);
    auto g = calc(d, c);
    ll ans = inf;

    //cerr<<f[27]<<" "<<g[27]<<endl;

    // for(int i = 13;i < 19;i++){
    //     cerr<<f[i]<<" ";
    // }
    // cerr<<endl;

    // for(int i = 13;i < 19;i++){
    //     cerr<<g[i]<<" ";
    // }
    // cerr<<endl;

    for(int i = 13;i < 19;i++){
        ans = min(ans, f[i] + g[27]);
        ans = min(ans, g[i] + f[27]);
    }

    for(int i = 13;i < 19;i++){
        for(int j = 13;j < 19;j++){
            if(i == j){
                if(i == 13 || i == 18)continue;
            }
            ans = min(ans, f[i] + g[j]);
        }
    }
    cout<<ans<<endl;
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