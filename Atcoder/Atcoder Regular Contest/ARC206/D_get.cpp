#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.27 11:01:29

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    iota(a.begin(),a.end(), 1);
    map<int,vector<int>>mp;
    do{
        vector<int>lis(n + 1),lds(n + 1);
        int lislen = 0, ldslen = 0;
        int len = 1 << n;
        for(int i = 0;i < len;i++){
            vector<int>seq;
            for(int j = 0;j < n;j++){
                if(i >> j & 1){
                    seq.push_back(a[j]);
                }
            }
            int islis = 1, islds = 1;
            for(int j = 0;j + 1 < seq.size();j++){
                if(seq[j] > seq[j + 1])islis = 0;
                else islds = 0;
            }
            if(islis){
                if(seq.size() > lislen){
                    lis.assign(n + 1, 0);
                    lislen = seq.size();
                }
                if(seq.size() == lislen){
                    for(auto x : seq)lis[x] = 1; 
                }
            }
            if(islds){
                if(seq.size() > ldslen){
                    lds.assign(n + 1, 0);
                    ldslen = seq.size();
                }
                if(seq.size() == ldslen){
                    for(auto x : seq)lds[x] = 1;
                }
            }
        }
        int k = 0;
        for(int i = 1;i <= n;i++){
            //cerr<<lis[i]<<" "<<lds[i]<<endl;
            if(lis[i] && lds[i])k++;
        }
        mp[k] = a;
        // for(auto x : a){
        //     cerr<<x<<" ";
        // }
        // cerr<<endl;
        // cerr<<"K = "<<k<<endl;

    }while(next_permutation(a.begin(),a.end()));

    for(auto [k, vec]:mp){
        cout<<k<<endl;
        for(auto x : vec){
            cout<<x<<" ";
        }
        cout<<endl;
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