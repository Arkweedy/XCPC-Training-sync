#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class segtree
{
    int n;
    vector<pair<int,int>>t2;//idx, val
    vector<int>lazy;
public:
    segtree(int n_)
    {
        n =  n_;
        t2.resize(n * 4);
        lazy.resize(n * 4);
        build_val(0,n-1,1);
    }
private:

    void push_up_val(int p)//minval, maxpos
    {
        if(t2[p * 2 + 1].second > t2[p * 2].second){
            t2[p] = t2[p * 2];
        }else{
            t2[p] = t2[p * 2 + 1];
        }
    }

    void push_down_val(int p)
    {
        t2[p * 2].second += lazy[p];
        t2[p * 2 + 1].second += lazy[p];
        lazy[p * 2] += lazy[p];
        lazy[p * 2 + 1] += lazy[p];
        lazy[p] = 0;
    }


    void build_val(int l, int r, int p)
    {
        if(l == r){
            t2[p] = make_pair(l,0);
        }else{
            int m = l + r >> 1;
            build_val(l,m,p*2);
            build_val(m+1,r,p*2+1);
            push_up_val(p);
        }
    }

    void range_add(int s, int t, int v, int l, int r, int p)
    {
        if(l>= s && r<=t){
            t2[p].second += v;
            lazy[p] += v;
        }else{
            int m = l + r >> 1;
            push_down_val(p);
            if(m >= s)
            range_add(s,t,v,l,m,p*2);
            if(m < t)
            range_add(s,t,v,m+1,r,p*2+1);
            push_up_val(p);
        }
    }

    int qry(int pos, int l ,int r, int p)
    {
        if(l == pos && r == pos){
            return t2[p].second;
        }else{
            int m = l + r >> 1;
            push_down_val(p);
            if(pos <= m)return qry(pos,l,m,p*2);
            else return qry(pos,m+1,r,p*2+1);
        }
    }

public:

    void range_add(int l ,int r, int v)
    {
        range_add(l,r,v,0,n-1,1);
    }

    pair<int,int> get_ans()
    {
        return t2[1];
    }

    int qry(int pos)
    {
        return qry(pos,0,n-1,1);
    }

};


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    segtree t(n + 1);
    for(int i = 0;i <= n;i++){
        t.range_add(i,i,i);
    }
    t.range_add(0,n-1,1);
    t.range_add(0,n-1,-1);

    auto check = [&](int x)->ll
    {
        int l = -1 ,r = -1;
        int lmi = 0, rmi = 0;
        ll lsum = 0, rsum = 0;
        vector<int>tmp;
        for(int i = 0;i < n;i++){ 
            int y = min(x, a[i]);
            if(y > lmi){
                t.range_add(y,x,-1);
                lsum += i;
                tmp.push_back(i);
                auto res = t.get_ans();
                if(res.second == 0)lmi = max(lmi,res.first);
            }
            if(t.qry(x) == 0){
                l = i;
                break;
            }
        }
        for(auto i : tmp){
            int y = min(x, a[i]);
            t.range_add(y,x,1);
        }
        tmp.clear();
    
        for(int i = n - 1;i >= 0;i--){
            int y = min(a[i],x);
            if(y > rmi){   
                t.range_add(y,x,-1);
                rsum += i;
                tmp.push_back(i);
                auto res = t.get_ans();
                if(res.second == 0)rmi = max(rmi,res.first);
            }
            if(t.qry(x) == 0){
                r = i;
                break;
            }
        }
        for(auto i : tmp){
            int y = min(x, a[i]);
            t.range_add(y,x,1);
        }
        tmp.clear();
      
        if(l == -1 || r == -1){
            return false;
        }else if(l >= r){
            return false;
        }else{
            return rsum - lsum;
        }
    };

    int l = 0, r = n / 2 + 1;
    ll ans = 0;
    while(r - l > 1){
        int m = l + r >> 1;
        ll res = check(m);
        if(res){
            ans = res;
            l = m;
        }else{
            r = m;
        }
    }
    ans = check(l);
    cout<<ans<<endl;
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