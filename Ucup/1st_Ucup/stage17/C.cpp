#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.31 16:42:29

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>a(n,vector<int>(n));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cin >> a[i][j];
            a[i][j]--;
        }
    }
    stack<int>st;
    vector<int>in(n);
    vector<pair<int,int>>ans;
    in[0] = 1;
    st.push(0);
    for(int i = 1;i < n;i++){
        int p = a[0][i];
        for(int j = 1;j < n;j++){
            if(in[a[p][j]]){
                while(st.top() != a[p][j]){
                    in[st.top()] = 0;
                    st.pop();
                }
                in[p] = 1;
                st.push(p);
                int u = p, v = a[p][j];
                if(u > v)swap(u, v);
                ans.emplace_back(u, v);
                break;
            }
        }
    }
    sort(ans.begin(),ans.end());

    for(auto [u, v] : ans){
        cout << u + 1 << " " << v + 1 << "\n";
    }
    //cout << endl;
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