#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//2106G2.cpp Create time : 2026.02.14 23:57

struct Actor{
    int n;
    int debug = 1;
    int root;
    int cnt = 0;
    vector<int>fa;
    vector<int>val;

    Actor(int n):n(n)
    {
        if(debug){
            cin >> root;
            root--;
            fa.resize(n);
            val.resize(n);
            for(int i = 0;i < n;i++){
                cin >> fa[i];
                fa[i]--;
                cerr << fa[i] << " ";
            }
            cerr << endl;
            for(int i = 0;i < n;i++){
                cin >> val[i];
            }
        }
    }

    int ask(vector<int>a)
    {
        cnt++;
        if(debug){
            int sum = 0;
            for(auto x : a){
                while(x != root){
                    sum += val[x];
                    x = fa[x];
                }
                sum += val[x];
            }
            cerr << "ask " << ", res = " << sum << endl;
            return sum;
        }
        else{
            cout << "? 1 " << a.size() << " ";
            for(auto x : a){
                cout << x + 1 << ' ';
            }
            cout << endl;
            int res;
            cin >> res;
            return res;
        }
    }

    void flip(int p)
    {
        cnt++;
        if(debug){
            val[p] = -val[p];
        }
        else{
            cout << "? 2 " << p << endl;
        }
        return;
    }

    void ans(int p)
    {
        if(debug){
            cerr << cnt << endl;
            cerr << "my ans is " << p + 1 << endl;
            assert(p == root);
            cerr << "Ans is ok" << endl;
        }
        cout << "! " << p + 1 << endl;
    }
};

//max query n + 200, find root, n~1e3

//1. flip P, all son of P changed
//2. f(root) != 0
//3. dep(p) >= abs(f(p))
// log n times ask a ancester(find a point not change)
// expect log_2 (dep / 2) times ? 



void solve()
{
    int n;
    cin >> n;
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
    }
    Actor act(n);
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    int p = g() % n;
    vector<int>all(n);
    iota(all.begin(),all.end(), 0);
    //need erase self
    auto check = [&](int p, vector<int>a)->bool // all changed(is all ancester)
    {
        int pre = act.ask(a);
        act.flip(p);
        int post = act.ask(a);
        return abs(pre - post) == a.size() * 2;
    };

    auto find = [&](auto&&self, int p, vector<int>a)->int // find anc
    {
        if(a.empty())return -1;
        if(a.size() == 1)return a[0];
        int m = a.size() / 2;
        vector<int>na, nb;
        for(int i = 0;i < a.size();i++){
            if(i < m)na.push_back(a[i]);
            else nb.push_back(a[i]);
        }
        int res = check(p, na);
        if(res == 0)return self(self, p, na);
        else return self(self, p, nb);
    };
    while(!check(p, all)){
        p = find(find, p, all);
    }

    act.ans(p);
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