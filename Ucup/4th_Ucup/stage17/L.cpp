#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;


void solve()
{
    int n;
    cin >> n;
    vector<int>x(n),y(n);
    for(int i = 0;i < n;i++){
        cin >> x[i] >> y[i];
    }
    vector<int>idx(n),idy(n);
    iota(idx.begin(),idx.end(),0);
    sort(idx.begin(),idx.end(), [&](int i, int j)->bool
    {
        return x[i] < x[j];
    });
    iota(idy.begin(),idy.end(),0);
    sort(idy.begin(),idy.end(), [&](int i, int j)->bool
    {
        return y[i] < y[j];
    });
    vector<int>stx(n), sty(n);
    int len = n / 3;
    for(int i = 0;i < n; i++){
        stx[idx[i]] = i / len;
        sty[idy[i]] = i / len;
    }
    // for(int i = 0;i < n; i++){
    //     cerr << stx[i] << " " << sty[i] << endl;
    // }
    i64 per = 1ll * n * n * 8 / 9;
    vector<vector<int>>ans;
    vector<vector<set<int>>>s(3, vector<set<int>>(3));
    for(int i = 0;i < n;i++){
        s[sty[i]][stx[i]].insert(i);
    }
    for(int k = 0;k < len;k++){
        vector<pair<int,int>>res;
        vector<int>p = {0, 1, 2};
        do{
            if(!s[0][p[0]].empty() && !s[1][p[1]].empty() && !s[2][p[2]].empty()){
                res.emplace_back(0, p[0]);
                res.emplace_back(1, p[1]);
                res.emplace_back(2, p[2]);
                break;
            }
        }while(next_permutation(p.begin(),p.end()));
        
        vector<int>a;
        for(auto [i, j] : res){
            int x = *(s[i][j].begin());
            s[i][j].erase(x);
            a.push_back(x);
        }
        ans.push_back(a);
    }

    cout << per << endl;
    for(int i = 0;i < len;i++){
        for(auto x : ans[i]){
            cout << x + 1 << " ";
        }
        cout << endl;
    }
    return;
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
