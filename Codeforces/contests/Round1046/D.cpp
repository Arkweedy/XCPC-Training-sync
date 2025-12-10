#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct actor{
    int n;
    int debug = 1;

    
    actor(int n_){
        n = n_;
    }

    int ask(vector<int>v)
    {
        if(debug){
            int s = 0;
            int res = 0;
            for(auto x : v){
                if(s + x <= n){
                    s += x;
                }
                else if(x <= n){
                    s = x;
                    res++;
                }
            }
            if(s != 0)res++;
            return res;
        }
        else{
            cout<<"? ";
            cout<<v.size();
            for(auto s : v){
                cout<<s<<" ";
            }
            cout<<endl;
            int res;
            cin>>res;
            return res;
        }
    }

    void ans(int x)
    {
        cout<<"! "<<x<<endl;
        return;
    }
};

mt19937 g(chrono::steady_clock::now().time_since_epoch().count());

void solve()
{
    constexpr int N = 100000;
    int W = g() % N + 1;
    actor act(W);

    
    int x = 1;
    vector<int>v(N, x);
    // int res = act.ask(v);
    // cout<<res<<endl;
   
    auto calc_range = [&](int res, int x)-> pair<int,int>
    {
        int l = -1, r = -1;
        for(int i = 1;i <= N;i++){
            int d = i / x;
            if(d == 0)continue;
            if((N + d - 1) / d == res){
                if(l == -1)l = i;
                r = i;
            }
        }
        return make_pair(l, r);
    };

    auto r1 = calc_range(act.ask(vector<int>(N, 1)),2);
    auto r2 = calc_range(act.ask(vector<int>(N, 2)),3);
    cout<<r1.first<<" "<<r1.second<<" "<<r2.first<<" "<<r2.second<<endl;

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