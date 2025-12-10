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
    vector<int>a(n);
    int pos = -1;
    for(int i = 0;i < n;i++){
        cin>>a[i];
        if(a[i] != -1)a[i];
        else pos = i;
    }
    int m = *max_element(a.begin(),a.end());
    vector<vector<int>>g(n);//less -> greater
    vector<vector<int>>round(m);
    vector<vector<int>>ok(m);
    vector<int>indeg(n);
    for(int i = 0;i < n;i++){
        if(a[i] == -1){
            for(int j = 0;j < m;j++){
                round[j].push_back(i);
                ok[j].push_back(1);
            }
        }else{
            for(int j = 0;j < a[i];j++){
                round[j].push_back(i);
                ok[j].push_back(j != a[i] - 1);
            }
        }
    }
    vector<int>ans(n);
    int l = 1, r = n;
    for(int i = 0;i < m;i++){
        auto get = [&]()->int
        {
            return i % 2 == 0 ? r-- : l++;
        };
        int len = ok[i].size();
        int x = 0, y = len - 1;
        for(int& j = x;j < len;j++){
            if(ok[i][j] == 1)break;
            else ans[round[i][j]] = get();
        }
        for(int& j = y;j >= 0;j--){
            if(ok[i][j] == 1)break;
            else ans[round[i][j]] = get();
        }
        for(int j = x;j <= y;j++){
            if(ok[i][j] == 0)ans[round[i][j]] = get();
        }
    }
    ans[pos] = l;
    for(int i  =0;i < n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
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