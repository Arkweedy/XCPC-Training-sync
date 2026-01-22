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
    int debug = 1;
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
            //update(res);
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
int p[100];
void solve()
{
    int n, x;
    //cin >> n >> x;
    n=10000;
    Actor actor(n);
    x = actor.x;
    int len = actor.len;
    vector<int>a(len),b(len);
    a[0] = b[0] = 1;
    map<int,int> mp;

    auto ok = [&](int x)->bool
    {
        if(abs(x)>n) return 1;
        if(mp[x]) return 0;
        mp[x]=1;
        vector<int>na,nb;
        if(x > 0){
            na = a;
            for(int i = len - 1;i - x >= 0;i--){
                na[i] = max(na[i], na[i - x]);
            }
            for(int i = 1;i < len;i++){
                if(na[i] == 1 && b[i] == 1){
                    return false;
                }
            }
            a = na;
            return true;
        }
        else{
            x = -x;
            nb = b;
            for(int i = len - 1;i - x >= 0;i--){
                nb[i] = max(nb[i - x], nb[i]);
            }
            for(int i = 1;i < len;i++){
                if(a[i] == 1 && nb[i] == 1){
                    return false;
                }
            }
            b = nb;
            return true;
        }
        assert(0);
        return true;
    };

    int k=10;
    int pa = n, pb = -n ;

    for(int i=0;i<k;i++) p[i]=n/k*i+1;
    int op=k-1;
    auto f = [&](bool sign)->int
    {
        op++;
        if(op==k-1) op=k;
        if(op==k) op=0;
        pa=p[op];
        if(sign == 1){//posi
            while(!ok(pa)){
                pa++;
            }
            p[op]=pa+1;
            return pa++;
        }
        else{
            while(!ok(pb)){
                pb++;
            }
            return pb++;
        }
    };

    int tot = 1;
    while(x--){
        cerr << tot++ << endl;
        actor.qry(f);
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