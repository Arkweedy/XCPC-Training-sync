#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;

using namespace std;

constexpr int N = 1e5 + 10;

void solve()
{ 
    int n, m;
    cin >> n >> m;
    //cerr << n << " " << m << endl;
    vector<int>x(n),y(n);
    for(int i = 0;i < n;i++){
        cin >> x[i] >> y[i];
        x[i] += N;
        y[i] += N;
    }
    vector<set<pair<int,int>>>sx(N * 2 + 10),sy(N * 2 + 10);
    vector<int>px(m),py(m);
    for(int i = 0;i < m;i++){
        cin >> px[i] >> py[i];
        px[i] += N;
        py[i] += N;
        sx[px[i]].insert({py[i], i});
        sy[py[i]].insert({px[i], i});
    }

   

    auto getxiny = [&](int x, int l, int r)->int //x , y in [l, r]
    {
        //cerr << "findx "<< x << " " << l << " " << r << " " << sx[x].size() << endl;
        auto it = sx[x].lower_bound({l, 0});
        if(it == sx[x].end())return -1;
        auto [v, p] = *it;
        //cerr << "find " << v << " " << p << endl;
        if(py[p] > r)return -1;
        return p;
    };

    auto getyinx = [&](int y, int l, int r)->int //x , y in [l, r]
    {
        //cerr << "findy " << l << " " << r << endl;
        auto it = sy[y].lower_bound({l, 0});
        if(it == sy[y].end())return -1;
        auto [v, p] = *it;
        //cerr << "find " << v << " " << p << " " << endl;
        if(px[p] > r)return -1;
        return p;
    };

    auto erase = [&](int p)->void
    {
        sx[px[p]].erase({py[p], p});
        sy[py[p]].erase({px[p], p});
    };

    vector<i64>d;
    i64 dis = 0;
    for(int i = 0;i < n;i++){
        //cerr << "at" << i << endl;
        if(x[i] == x[(i + 1) % n]){
            if(y[i] < y[(i + 1) % n]){//up
                vector<int>b;
                int p;
                int l = y[i], r = y[(i + 1) % n];
                while((p = getxiny(x[i], l, r)) != -1){
                    b.push_back(p);
                    erase(p);
                }
                for(auto p : b){
                    //cerr <<"#"<<p;
                    i64 dd = py[p] - l;
                    d.push_back(dd + dis);
                }
                dis += r - l;
            }
            else{//down
                vector<int>b;
                int p;
                int r = y[i], l = y[(i + 1) % n];
                while((p = getxiny(x[i], l, r)) != -1){
                    b.push_back(p);
                    erase(p);
                }
                reverse(b.begin(),b.end());
                for(auto p : b){
                    
                    i64 dd = r - py[p];
                    d.push_back(dd + dis);
                }
                dis += r - l;
            }
        }
        else{
            if(x[i] < x[(i + 1) % n]){//up
                //cerr << "at" << i << endl;
                vector<int>b;
                int p;
                int l = x[i], r = x[(i + 1) % n];
                //cerr << l << " " << r << " "<< y[i]<< endl;
                while((p = getyinx(y[i], l, r)) != -1){
                    erase(p);
                    b.push_back(p);
                }
                for(auto p : b){
                    //cerr <<"#"<<p;
                    i64 dd = px[p] - l;
                    d.push_back(dd + dis);
                }
                dis += r - l;
                //cerr << "end" << i << endl;
            }
            else{//down
                vector<int>b;
                int p;
                int r = x[i], l = x[(i + 1) % n];
                while((p = getyinx(y[i], l, r)) != -1){
                    erase(p);
                    b.push_back(p);
                }
                reverse(b.begin(),b.end());
                for(auto p : b){
                    //cerr <<"#"<<p;
                    i64 dd = r - px[p];
                    d.push_back(dd + dis);
                } 
                dis += r - l;
            }
        }
    }
 
    // cerr << "ok" << endl;
    // cerr << d.size() << endl;

    // cerr << dis << endl;
    // for(auto xx : d){
    //     cerr << xx << " ";
    // }
    // cerr << endl;
    
    i64 maxd = dis - d.back() + d[0];
    for(int i = 0;i < m - 1;i++){
        maxd = max(maxd, d[i + 1] - d[i]);
    }
    i64 ans = dis - maxd;
    cout << ans << endl;
    return;


    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}