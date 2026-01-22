#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.22 12:05:43
mt19937 g(chrono::steady_clock::now().time_since_epoch().count());

struct Actor{
    int n;
    int debug = 0;
    int x;
    int len;
    int ptr;
    vector<int>a, b;
    vector<int>lst;
    set<int>num;

    Actor(int n){
        this -> n = n;
        x = 2 * floor(sqrt(n)) - 1;
        len = n * x;
        a.resize(len);
        b.resize(len);
        a[0] = b[0] = 1;
        if(debug){
            lst.resize(n);
            ptr = 0;
            for(int i = 0;i < x;i++){
                cin >> lst[i];
            }
        }
    }

    void qry(function<int(bool)>f)
    {
        if(debug){
            int sign = lst[ptr++];
            int res = f(sign);
            assert(res * (sign ? 1 : -1)> 0) ;
            update(res);
        }
        else{
            char sign;
            cin >> sign;
            int res = f(sign == '+' ? 1 : 0);
            cout << res << endl;
        }
    }

    void update(int x)
    {
        cerr <<"update " << x << endl;
        if(x == 0){
            cerr << "output 0" << endl;
            assert(0);
        }
        if(num.count(x)){
            cerr <<"same number"<<endl;
            assert(0);
        }
        num.insert(x);
        if(x > 0){
            for(int i = len - 1;i - x >= 0;i--){
                a[i] = max(a[i], a[i - x]);
            }
        }
        else{
            x = -x;
            for(int i = len - 1;i - x >= 0;i--){
                b[i] = max(b[i - x], b[i]);
            }
        }
        
        for(int i = 1;i < len;i++){
            if(a[i] == 1 && b[i] == 1){
                cerr << "sum = 0" << endl;
                assert(0);
            }
        }
        return;
    }

    
};

void solve()
{
    int n, x;
    cin >> n >> x;
    Actor actor(n);
    actor.x = x;
    //int len = actor.len;
    // vector<int>a(len),b(len);
    // a[0] = b[0] = 1;

    // auto ok = [&](int x)->bool
    // {
    //     vector<int>na,nb;
    //     if(x > 0){
    //         na = a;
    //         for(int i = len - 1;i - x >= 0;i--){
    //             na[i] = max(na[i], na[i - x]);
    //         }
    //         for(int i = 1;i < len;i++){
    //             if(na[i] == 1 && b[i] == 1){
    //                 return false;
    //             }
    //         }
    //         a = na;
    //         return true;
    //     }
    //     else{
    //         x = -x;
    //         nb = b;
    //         for(int i = len - 1;i - x >= 0;i--){
    //             nb[i] = max(nb[i - x], nb[i]);
    //         }
    //         for(int i = 1;i < len;i++){
    //             if(a[i] == 1 && nb[i] == 1){
    //                 return false;
    //             }
    //         }
    //         b = nb;
    //         return true;
    //     }
    //     assert(0);
    //     return true;
    // };

    
    int pa = n, pb = -n + x - 1;
    auto f = [&](bool sign)->int
    {
        
        if(sign == 1){//posi
            return pa--;
        }
        else{
            return pb++;
        }
    };

    int tot = 1;
    while(x--){
        actor.qry(f);
    }
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