#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.14 21:08

void solve()
{
    int n, a, b;
    cin >> a >> b >> n;
    int h, w, m;
    h = a, w = b, m = n;
    set<pair<int,int>>sx, sy;
    vector<int>x(n), y(n);
    for(int i = 0;i < n;i++){
        cin >> x[i] >> y[i];
        sx.insert({x[i], i});
        sy.insert({y[i], i});
    }


    // // find 
    // vector<int>ix(n), iy(n);
    // iota(ix.begin(),ix.end(),[&](int i, int j)->bool
    // {
    //     return x[i] < x[j];
    // });
    // iota(iy.begin(),iy.end(),[&](int i, int j)->bool
    // {
    //     return y[i] < y[j];
    // });

    int offx = 0, offy = 0;
    vector<int>ansx(n), ansy(n);

    while(n--){
        auto [ix, xid] = *sx.lower_bound({a, 0});
        if(ix == a){
            ansx[xid] = offx + 1;
            ansy[xid] = offy + 1;
            //cerr <<"put " << xid + 1 <<"("<<x[xid]<<","<<y[xid]<<")"<< " at " << offx + 1 << " , " << offy + 1 << endl;
            offy += y[xid];

            sx.extract({x[xid], xid});
            sy.extract({y[xid], xid});
            b -= y[xid];
        }
        else{
            auto [iy, yid] = *sy.lower_bound({b, 0});
            assert(iy == b);
            ansx[yid] = offx + 1;
            ansy[yid] = offy + 1;
            //cerr <<"put " << yid + 1 <<"("<<x[yid]<<","<<y[yid]<<")"<< " at " << offx + 1 << " , " << offy + 1 << endl;
            offx += x[yid];
            sx.extract({x[yid], yid});
            sy.extract({y[yid], yid});
            a -= x[yid];
        }
        
    }

    // cerr << "ok" << endl;
    // cerr << h << " " << w << endl;

    // vector<vector<int>>c(h, vector<int>(w));
    

    for(int i = 0;i < ansx.size();i++){
        cout << ansx[i] << " "  << ansy[i] << "\n";
        // for(int j = 0;j < x[i];j++){
        //     for(int k = 0;k < y[i];k++){
        //         c[ansx[i] + j - 1][ansy[i] + k - 1] = i;
        //     }
        // }
    }
    return;


    // for(int i = 0;i < h;i++){
    //     for(int j = 0;j < w;j++){
    //         cerr << c[i][j] << " ";
    //     }
    //     cerr << endl;
    // }
    // return;
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