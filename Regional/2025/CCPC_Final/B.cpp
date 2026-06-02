#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.04.26 17:36:41

struct Actor{
    int n;
    int debug = 0;
    int cnt = 0;
    vector<int>p,pos;
    map<pair<int,int>, int>mp;

    Actor(int n_){
        n = n_;
        p.resize(n);
        pos.resize(n);
        if(debug == 1){
            p = {1,0,2,3};
            //p = {2,1,3,4};
        }
        else if(debug == 2){
            iota(p.begin(),p.end(), 0);
            mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
            shuffle(p.begin(),p.end(), g);
            if(p[0] > p[n - 1])reverse(p.begin(),p.end());
        }
        for(int i = 0;i < n;i++){
            pos[p[i]] = i;
        }
        cerr << "P is : " << endl;
        for(int i = 0;i < n;i++){
            cerr << p[i] << " ";
        }
        cerr << endl;
    }

    int ask(int x, int y)
    {
        if(x == y)return 0;
        if(mp.count({x, y}))return mp[{x, y}];
        cnt++;
        if(debug){
            return abs(pos[x] - pos[y]) % 3;
        }
        else{
            cout << "? " << x + 1 << " " << y + 1 << endl;
            int res;
            cin >> res;
            return mp[{x, y}] = mp[{y, x}] = res;
        }
    }

    void solve(vector<int>a)
    {
        if(debug){
            for(int i = 0;i < n;i++){
                //assert(a[i] == p[i]);
                if(a[i] != p[i]){
                    cerr << "EXPECTED" << endl;
                    for(int i = 0;i < n;i++){
                        cerr << p[i] << " ";
                    }
                    cerr << endl;
                    cerr << "OUTPUT" << endl;
                    for(int i = 0;i < n;i++){
                        cerr << a[i] << " ";
                    }
                    cerr << endl;
                    assert(0);
                }
            }
            cout << "PASSED AVE = " << cnt / double(n) << endl;
        }
        else{
            cout << "! ";
            for(int i = 0;i < n;i++){
                cout << a[i] + 1 << " ";
            }
            cout << endl;
        }
    }
};


void solve()
{
    int n;
    cin >> n;
    Actor actor(n);
    vector<vector<int>>a(3);
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    
    auto ra = [&]()->int
    {
        return g() % n;
    };
    vector<int>rem;
    int x = ra();
    for(int i = 0;i < n;i++){
        if(actor.ask(x, i) == 0){
            a[0].push_back(i);
        }
        else{
            rem.push_back(i);
        }
    }
    int y = rem[g() % rem.size()];
    for(int i = 0;i < rem.size();i++){
        if(actor.ask(y, rem[i]) == 0){
            a[1].push_back(rem[i]);
        }
        else{
            a[2].push_back(rem[i]);
        }
    }

    vector<int>ans;

    auto findL = [&](auto&&self, vector<vector<int>>R)->int
    {
        if(R[1].empty() && R[2].empty()){
            return -1;
        }
        if(R[1].empty()){
            assert(0);
        }
        if(R[2].empty()){
            return R[1].back();
        }
        if(R[1].size() <= R[2].size()){
            int x = R[1][g() % R[1].size()];
            vector<int>nR;
            for(auto y : R[2]){
                if(actor.ask(x, y) == 2){
                    nR.push_back(y);
                }
            }
            if(nR.empty())return x;
            R[2] = move(nR);
        }
        else{
            int x = R[2][g() % R[2].size()];
            vector<int>nR;
            for(auto y : R[1]){
                if(actor.ask(x, y) == 1){
                    nR.push_back(y);
                }
            }
            if(nR.empty())return x;
            R[1] = move(nR);
        }
        return self(self, R);
    };

    auto dfs = [&](auto&&self, vector<vector<int>>a)->void
    {
        if(a[0].empty()){
            if(!a[1].empty())ans.push_back(a[1][0]);
            if(!a[2].empty())ans.push_back(a[2][0]);
            return;
        }
        int sz = a[0].size();
        int z = a[0][g() % sz];
        vector<vector<int>>L(3),R(3);
        for(auto x : a[1]){
            if(actor.ask(x, z) == 1){
                R[1].push_back(x);
            }
            else{
                L[1].push_back(x);
            }
        }
        for(auto x : a[2]){
            if(actor.ask(x, z) == 2){
                R[2].push_back(x);
            }
            else{
                L[2].push_back(x);
            }
        }
        int l = findL(findL, R);
        
        if(l == -1){
            L[0] = move(a[0]);
            L[0].erase(find(L[0].begin(),L[0].end(), z));
        }
        else{
            for(auto x : a[0]){
                if(x == z)continue;
                if(actor.ask(x, l) == 1){
                    L[0].push_back(x);
                }
                else{
                    R[0].push_back(x);
                }
            }
        }
        
        self(self, L);
        ans.push_back(z);
        self(self, R);
        
        return;
    };

    dfs(dfs, a);
    assert(ans.size() == n);
    if(ans[0] > ans[n - 1]){
        reverse(ans.begin(),ans.end());
    }

    actor.solve(ans);
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