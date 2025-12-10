#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.16 23:47:48
constexpr int debug = 1;
struct actor
{
    int n;
    int cnt;
    vector<int>a;

    actor(int n_)
    {
        cnt = 0;
        this -> n = n_;
        if(debug){
            a.resize(n);
            iota(a.begin(),a.end(), 1);
            mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
            shuffle(a.begin(),a.end(), g);
        }
    }

    pair<int,int>ask(set<int>s)
    {
        cnt++;
        if(debug){
            // cerr<<"ask : ";
            // for(auto x : s)cerr<<x<<" ";
            // cerr<<endl;
            vector<int>b;
            for(auto x : s){
                b.push_back(a[x]);
            }
            sort(b.begin(),b.end());
            return make_pair(b[1], b[2]);
        }
        else{
            cout<<"? ";
            cout << s.size() << " ";
            for(auto x : s){
                cout << x + 1 << " ";
            }
            cout<<endl;
            int x, y;
            cin >> x >> y;
            return make_pair(x, y);
        }
    }

    void answer(int x, int y)
    {
        cerr<<cnt<<endl;
        if(debug){
            if(a[x] > a[y])swap(x, y);
            assert(a[x] == n / 2 && a[y] == n / 2 + 1);
            assert(cnt <= 80);
            return;
        }
        else{
            cout<<"! "<<x + 1<<" "<<y + 1<<endl;
            return;
        }
    }
};

void solve()
{
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    int n;
    n = 100;
    // n = g() % 94 + 6;
    // if(n % 2 == 1)n++;
    //cin >> n;
    actor act(n);
    

    if(n == 6){
        set<set<int>>all;
        set<int>s;
        while(1){
            s.clear();
            while(s.size() != 4){
                int y = g() % n;
                s.insert(y);
            }
            if(all.count(s))continue;
            all.insert(s);
            auto [x, y] = act.ask(s);
            if(x == 2 && y == 5)break;
        }
        vector<int>ne(6);
        for(auto x : s){
            ne[x] = 1;
        }
        int x = -1, y = -1;
        for(int i = 0;i < 6;i++){
            if(!ne[i] && x == -1)x = i;
            else if(!ne[i]) y = i;
        }
        act.answer(x, y);
        return;
    }

    int k = n / 2;
    //find k, k + 1
    set<int>a, b;
    //vector<int>id(n);
    vector<int>ida(n / 2), idb(n / 2);
    iota(ida.begin(),ida.end(), 0);
    iota(idb.begin(),idb.end(), n / 2);
    //iota(id.begin(),id.end(), 0); // 0base
    //shuffle(id.begin(),id.end(), g);
    shuffle(ida.begin(),ida.end(), g);
    shuffle(idb.begin(),idb.end(), g);
    int ok = 0;
    auto find = [&]()->void
    {
        //assert(ida.size() > 1);
        if(ida.size() == 1){
            int x = ida[0], y = idb[0];
            if(a.empty())a = {x,y};
            if(b.empty())b = {x,y};
        }
        assert(ida.size() == idb.size());
        vector<int>nida, nidb;
        for(int i = 0;i + 1 < ida.size();i += 2){
            set<int>s;
            s.insert(ida[i]);
            s.insert(ida[i + 1]);
            s.insert(idb[i]);
            s.insert(idb[i + 1]);
            auto [x, y] = act.ask(s);
            if(x > y)swap(x, y);

            if(x == k || y == k){//s
                a = s;
                if(y == k)for(auto x : s)nida.push_back(x);
            }
            if(x == k + 1 || y == k + 1){//big
                b = s;
                if(x == k + 1)for(auto x : s)nidb.push_back(x);
            }
            if(y < k){//s
                for(auto x : s)nida.push_back(x);
            }
            if(x > k + 1){//big
                for(auto x : s)nidb.push_back(x);
            }
        }
        if(ida.size() % 2 == 1){
            nida.push_back(ida.back());
            nidb.push_back(idb.back());
        }
        while(nida.size() > nidb.size()){
            nidb.push_back(nida.back());
            nida.pop_back();
        }
        while(nidb.size() > nida.size()){
            nida.push_back(nidb.back());
            nidb.pop_back();
        }
        shuffle(nida.begin(),nida.end(), g);
        shuffle(nidb.begin(),nidb.end(), g);
        ida = move(nida);
        idb = move(nidb);
        if(!a.empty() && !b.empty())ok = 1;
        return;
    };

    while(!ok)find();
    cerr<<act.cnt<<" ";

    // a -> k 
    // b -> k + 1

    auto check = [&](set<int>s, int t)->int
    {
        for(auto x : s){
            set<int>ns;
            ns.insert(x);
            while(ns.size() != 4){
                int y = g() % n;
                if(!s.count(y)){
                    ns.insert(y);
                }
            }
            auto [rx, ry] = act.ask(ns);
            if(rx == t || ry == t)return x;
        }
        return -1;
    };

    int ansx = -1, ansy = -1;
    while(ansx == -1){
        ansx = check(a, k);
    }
    while(ansy == -1){
        ansy = check(b, k + 1);
    }
    act.answer(ansx,ansy);
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