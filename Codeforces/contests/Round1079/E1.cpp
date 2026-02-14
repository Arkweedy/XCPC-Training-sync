#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E1.cpp Create time : 2026.02.11 23:45

void solve()
{
    int n;
    cin >> n;

    auto ask = [&](int k)->vector<int>
    {
        cout << "? " << k << endl;
        int c;
        cin >> c;
        vector<int>path(c);
        for(int i = 0;i < c;i++){
            cin >> path[i];
        }
        return path;
    };

    
    vector<set<int>>g(n + 1);

    auto ans = [&]()->void
    {
        
        int sum = 0;
        for(int i = 1;i <= n;i++){
            for(auto s : g[i]){
                sum++;
            }
        }

        cout << "! " << sum << endl;
        for(int i = 1;i <= n;i++){
            for(auto s : g[i]){
                cout << i << " " << s << endl;
            }
        }
        return;
    };

    //binary 

    //query path sum cnt
    //n, m -> up : ?

    int l = n; 
    int r = (1 << 20) + 1;
    //int r = 30;

    while(r - l > 1){
        int m = l + r >> 1;
        if(ask(m).empty()){
            r = m;
        }
        else{
            l = m;
        }
    }

    int sum = l;

    auto nomid = [&](vector<int>a, vector<int>b)->bool
    {
        if(a[0] == b[0]){
            if(a.size() == 1){
                if(b[1] == 1)return true;
                else return false;
            }
            else{
                if(a[1] + 1 >= b[1])return true;
                else return false;
            }
        }
        else if(a[0] + 1 == b[0]){
            if(a.size() == 1)return false;
            else if(a[1] < n)return false;
            else if(b.size() == 1)return true;
            else if(b[1] == 1)return true;
            else return false;
        }
        else{
            return false;
        }
    };

    auto put = [&](vector<int>&a)->void
    {
        if(a.size() > 1){
            //cerr << "put " << a[0] << " " << a[1] << endl;
            g[a[0]].insert(a[1]);
        }
        return;
    };


    auto cdq = [&](auto&&self, int l, int r, vector<int>&lres, vector<int>&rres)->void
    {
        //cerr << "cdq " << l  << " " << r << endl;
        if(l + 1 >= r){
            put(lres);
            put(rres);
            return;
        }
        int m = l + r >> 1;
        auto mres = ask(m);
        if(!nomid(lres, mres)){
            self(self, l, m, lres, mres);
        }
        else{
            put(lres);
            put(rres);
        }
        if(!nomid(mres, rres)){
            self(self, m, r, mres, rres);
        }
        else{
            put(lres);
            put(rres);
        }
        put(mres);
        return;
    };

    vector<int>as(1, 1);
    auto bs = ask(sum);
    cdq(cdq, 1, sum, as, bs);
    ans();
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