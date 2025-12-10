#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.29 10:21:19

//maybe dp
//O(n^3) 
//dp[1][n] = max(dp[1][x] + dp[x + 1][n])
//

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n * 2);
    for(int i = 0;i < n * 2;i++){
        cin>>a[i];
    }
    auto b = a;
    nth_element(b.begin(),b.begin() + n, b.end());
    int mr = b[n];
    int c = 0;
    for(int i = 0;i < n;i++){
        if(b[i] == mr)c++;
    }
    string ans(n * 2, ' ');
    int last = 0;
    int sum = 0;
    vector<int>tag(n * 2);

    auto get = [&](int l, int r)->void
    {
        for(int i = l;i <= r;i++){
            if(tag[i] == tag[l])ans[i] = '(';
            else ans[i] = ')';
        }
        return;
    };

    for(int i = 0;i < n * 2;i++){
        if(a[i] < mr){
            tag[i] = 1;
        }
        else if(a[i] == mr && c){
            tag[i] = 1;
            c--;
        }
        else{
            tag[i] = -1;
        }
        sum += tag[i];
        if(sum == 0){
            get(last, i);
            last = i + 1;
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
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}