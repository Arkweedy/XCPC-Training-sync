#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());

constexpr ll inf = 1e9;
constexpr ll INF = 2e9;

struct actor{
    int debug = 0;
    int n;
    vector<ll>x;
    vector<ll>y;

    ll ax, ay;
    ll ansx, ansy;

    // actor()
    // {
    //     n = 3;
    //     ax = ansx = 0;
    //     ay = ansy = 0;
    //     x = {1, 9, 3};
    //     y = {-8,2, 1};
    // }


    actor(int n_)
    {
        this->n = n_;
        x.resize(n);
        y.resize(n);
        if(debug){
            ax = ll(g() % INF) - inf;
            ay = ll(g() % INF) - inf;
            ansx = ax;
            ansy = ay;
            cerr<<"ans is"<<endl;
            cerr<<ansx<<" "<<ansy<<endl;
            for(int i = 0;i < n;i++){
                x[i] = ll(g() % INF) - inf;
                y[i] = ll(g() % INF) - inf;
                cerr<<x[i]<<" "<<y[i]<<endl;
            }
        }
        else{
            for(int i = 0;i < n;i++){
                cin>>x[i]>>y[i];
            }
        }
    }

    ll query(char op, ll d)
    {
        if(debug){
            if(op == 'U'){
                ay += d;
            }
            else if(op == 'D'){
                ay -= d;
            }
            else if(op == 'L'){
                ax -= d;
            }
            else if(op == 'R'){
                ax += d;
            }

            ll res = LLONG_MAX / 2;
            for(int i = 0;i < n;i++){
                res = min(res, abs(ax - x[i]) + abs(ay - y[i]));
            }
            return res;
        }
        else{
            cout<<"? "<<op<<" "<<d<<endl;
            ll res;
            cin>>res;
            return res;
        }
    }

    void ans(ll x, ll y)
    {
        if(debug){
            cerr<<"my ans is "<<endl;
            cerr<<x<<" "<<y<<endl;
            assert(ansx == x && ansy == y);
        }
        else{
            cout<<"! "<<x<<" "<<y<<endl;
        }
        return;
    }
};

void solve()
{
    int n;
    cin>>n;
    actor act(n);
    vector<ll>p1(n),p2(n);
    auto& x = act.x, &y = act.y;
    for(int i = 0;i < n;i++){
        p1[i] = x[i] + y[i];
        p2[i] = x[i] - y[i];
    }
    sort(p1.begin(),p1.end());
    sort(p2.begin(),p2.end());

    ll ma1 = p1.back(), ma2 = p2.back();
    //cerr<<"ma : "<<ma1<<" "<<ma2<<endl;

    constexpr ll k = inf;
    act.query('R', k);
    act.query('R', k);
    act.query('U', k);
    ll res1 = act.query('U', k);
    act.query('D', k);
    act.query('D', k);
    act.query('D', k);
    ll res2 = act.query('D', k);

    //cerr<<res1<<" "<<res2<<endl;

    //res1 = ax + ay + 4k - ma1
    //res2 = ax - ay + 4k - ma2

    res1 -= 4 * k - ma1;
    res2 -= 4 * k - ma2;

    ll ansx = (res1 + res2) / 2;
    ll ansy = (res1 - res2) / 2;
    //cerr<<ansx<<" "<<ansy<<endl;

    act.ans(ansx,ansy);
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