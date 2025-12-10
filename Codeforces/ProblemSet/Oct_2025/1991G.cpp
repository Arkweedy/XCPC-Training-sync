#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m,k,q;
    cin>>n>>m>>k>>q;
    string s;
    cin>>s;
    

    int dfull = 0, rfull = 0;
    int dptr = 0, rptr = 0;//heap, pointer to empty [0,n - k) [0,m - k)
    int dp = 0, rp = 0;//delete match, [0, k)
    int dbuf = 0, rbuf = 0; //[0, k)
    vector<pair<int,int>>ans;

    auto ind = [&]()->void
    {
        ans.emplace_back(k + dptr, 0);
        dptr++;
        if(dptr == n - k){
            dfull = 1;
            dptr = 0;
            dp = rbuf;
            rbuf = 0;
        }
        return;
    };

    auto inr = [&]()->void
    {
        ans.emplace_back(0,k + rptr);
        rptr++;
        if(rptr == m - k){
            rfull = 1;
            rptr = 0;
            rp = dbuf;
            dbuf = 0;
        }
        return;
    };

    auto matchr = [&]()->void
    {
        ans.emplace_back(rp, 0);
        rp++;
        if(rp == k){
            rfull = 0;
            rp = 0;
        }
        return;
    };

    auto matchd = [&]()->void
    {
        ans.emplace_back(0, dp);
        dp++;
        if(dp == k){
            dfull = 0;
            dp = 0;
        }
        return;
    };

    auto dina = [&]()->void
    {
        ans.emplace_back(dbuf, 0);
        dbuf++;
        if(dbuf == k){
            dbuf = 0;
            dptr = 0;
            rbuf = dp;
            dp = 0;
            dfull = 0;
        }
    };

    auto rina = [&]()->void
    {
        ans.emplace_back(0, rbuf);
        rbuf++;
        if(rbuf == k){
            rbuf = 0;
            rptr = 0;
            dbuf = rp;
            rp = 0;
            rfull = 0;
        }
    };

    auto add_d = [&]()->void
    {
        if(!dfull)ind();
        else if(rfull)matchr();
        else dina();
    };

    auto add_r = [&]()->void
    {
        if(!rfull)inr();
        else if(dfull)matchd();
        else rina(); 
    };

    if(k == 1){
        int d = 0;
        for(auto ch : s){
            ans.emplace_back(0,d++);
            d %= m;
        }
    }
    else if(n == k && m == k){
        for(auto ch : s){
            ans.emplace_back(0,0);
        }
    }
    else if(n == k){
        int d = 0;
        for(auto ch : s){
            if(ch == 'H'){
                ans.emplace_back(d++, 1);
                d %= k;
            }
            else ans.emplace_back(0,0);
        }
    }
    else if(m == k){
        int r = 0;
        for(auto ch : s){
            if(ch == 'H')ans.emplace_back(0,0);
            else{
                ans.emplace_back(1,r++);
                r %= k;
            }
        }
    }
    else{
        for(auto ch : s){
            if(ch == 'H')add_d();
            else add_r();
        }
    }

    for(auto [x, y] : ans){
        cout<<x + 1<<" "<<y + 1<<"\n";
    }


    // vector<vector<int>>a(n,vector<int>(m));
    // auto print = [&]()->void
    // {
    //     for(int i = 0;i < n;i++){
    //         for(int j = 0;j < m;j++){
    //             cerr<<a[i][j];
    //         }
    //         cerr<<endl;
    //     }
    //     cerr<<endl;
    // };
    // auto clear = [&]()->void
    // {
    //     vector<int>row,col;
    //     for(int i = 0;i < n;i++){
    //         int ok = 1;
    //         for(int j = 0;j < m;j++){
    //             if(a[i][j] == 0)ok = 0;
    //         }
    //         if(ok)row.push_back(i);
    //     }
    //     for(int i = 0;i < m;i++){
    //         int ok = 1;
    //         for(int j = 0;j < n;j++){
    //             if(a[j][i] == 0)ok = 0;
    //         }
    //         if(ok)col.push_back(i);
    //     }
    //     for(auto x : row){
    //         for(int i = 0;i < m;i++){
    //             a[x][i] = 0;
    //         }
    //     }
    //     for(auto y : col){
    //         for(int i = 0;i < n;i++){
    //             a[i][y] = 0;
    //         }
    //     }
    //     return;
    // };
    // for(int i = 0;i < ans.size();i++){
    //     auto [x, y] = ans[i];
    //     cerr<<"step "<<i + 1<<" add "<<s[i]<<" at "<<x<<" "<<y<<endl;
    //     if(s[i] == 'H'){
    //         for(int j = 0;j < k;j++){
    //             assert(a[x][y + j] == 0);
    //             a[x][y + j] = 1;
    //         }
    //     }
    //     else{
    //         for(int j = 0;j < k;j++){
    //             assert(a[x + j][y] == 0);
    //             a[x + j][y] = 1;
    //         }
    //     }
    //     //print();
    //     clear();
    //     //print();
    // }


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