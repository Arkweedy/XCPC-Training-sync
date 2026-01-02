#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.02 13:55:04

void solve()
{
    vector<string>ss(3);
    cin >> ss[0] >> ss[1] >> ss[2];
    string t = "cerc";
    vector<int>id = {0, 1, 2};
    do{
        //cerr << id[0] << ' ' << id[1] << " " << id[2] << endl;
        for(int i = 0;i < 8;i++){
            string s;
            vector<int>res;
            for(int j = 0;j < 3;j++){
                if((i >> j) & 1){
                    s += ss[id[j]];
                    res.push_back(id[j]);
                }
            }
            if(s == t){
                cout << "YES" << endl;
                cout << res.size() << endl;
                for(auto x : res) cout << x + 1 << " ";
                cout << endl;
                goto out;
            }
        }
    }while(next_permutation(id.begin(),id.end()));
    cout << "NO"<<endl;
    out : 
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