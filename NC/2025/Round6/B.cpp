#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
#define int long long


void solve()
{
    int n,y,m;
    cin>>n>>y>>m;
    vector<vector<int>>a(n);
    vector<int>pos1;
    int x = -1;
    for(int i = 0;i < n;i++){
        int k;
        cin>>k;
        if(x == -1 && k == 1)x = i;
        if(k == 1)pos1.push_back(i);
        a[i].resize(k);
        for(int j = 0;j < k;j++){
            cin>>a[i][j];
        }
    }

    auto check_trans = [&](int i, ll p)->bool
    {
        for(int j = 0;j < a[i].size();j++){
            if(p <= a[i][j])return false;
        }
        return true;
    };

    auto check_nout = [&](int i, ll p, ll limit)->bool
    {
        ll res = 0;
        for(int j = 0;j < a[i].size();j++){
            res *= p;
            res += a[i][j];
            if(res > limit)return false;
        }
        return true;
    };

    auto next = [&](int i, ll p)->ll
    {
        ll res = 0;
        for(int j = 0;j < a[i].size();j++){
            res *= p;
            res += a[i][j];
        }
        return res;
    };

    //range ok
    if(x == -1){
        int l = 2, r = m + 1;
        auto check = [&](int p)->bool
        {
            ll res = p;
            for(int i = 0;i < n;i++){
                ll nres = 0;
                for(int j = 0;j < a[i].size();j++){
                    nres *= res;
                    nres += a[i][j];
                    if(nres > y){cerr<<nres<<endl;return false;}
                    //can not check res > a[i][j]
                }
                res = nres;
                
            }
            return res <= y;
        };
        auto check2 = [&](int p)->bool
        {
            ll res = p;
            for(int i = 0;i < n;i++){
                ll nres = 0;
                if(!check_trans(i,res))return false;

                for(int j = 0;j < a[i].size();j++){
                    nres *= res;
                    nres += a[i][j];
                    if(nres > y)return false;
                }
                res = nres;
            }
            return res == y;
        };
        while(r - l > 1){
            int m = l + r >> 1;
            if(check(m)){
                l = m;
            }
            else{
                r = m;
            }
        }
        if(check2(l))cout<<l<<" "<<l<<endl;
        else cout<<-1<<" "<<-1<<endl;
    }
    else{
        //check first pos1
        //0->x
        int z = a[x][0];
        auto check = [&](int p)->bool
        {
            ll res = p;
            for(int i = 0;i < x;i++){
                ll nres = 0;
                if(!check_trans(i,res)){
                    return false;
                }
                for(int j = 0;j < a[i].size();j++){
                    nres *= res;
                    nres += a[i][j];
                    if(nres > z)return true;
                }
                res = nres;
            }
            return res > z;
        };

        int l = 1, r = m + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            if(check(m)){
                r = m;
            }
            else{
                l = m;
            }
        }
        //r is min ok
        //[r, m]
        if(r > m){
            cout<<-1<<" "<<-1<<endl;
            return;
        }
        
        //check m
        auto gonext = [&](ll p, int l, int r, int limit)->ll //[l,r)
        {
            ll res = p;
            for(int i = l;i < r;i++){
                ll nres = 0;
                if(!check_trans(i,res))return -1;
                for(int j = 0;j < a[i].size();j++){
                    nres *= res;
                    nres += a[i][j];
                    if(nres > limit){
                        return nres;
                    }
                }
                res = nres;
            }
            return res;
        };

        //first pos1 ->last pos1
        ll res = z;
        for(int i = 0;i < pos1.size() - 1;i++){
            res = gonext(res, pos1[i] + 1,pos1[i + 1],a[pos1[i + 1]][0]);
            if(res > a[pos1[i + 1]][0]){
                res = a[pos1[i + 1]][0];
            }
            else{
                cout<<-1<<" "<<-1<<endl;
                return;
            }
        }

        //last pos1 ->end
        for(int i = pos1.back() + 1;i < n;i++){
            ll nres = 0;
            if(!check_trans(i,res)){
                cout<<-1<<" "<<-1<<endl;
                return;
            }
            for(int j = 0;j < a[i].size();j++){
                nres *= res;
                nres += a[i][j];
                if(nres > y){
                    cout<<-1<<" "<<-1<<endl;
                    return;
                }
            }
            res = nres;
        }
       
        if(res == y){
            cout<<r<<" "<<m<<endl;
        }
        else{
            cout<<-1<<" "<<-1<<endl;
        }
    }
    return;
}

signed main()
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