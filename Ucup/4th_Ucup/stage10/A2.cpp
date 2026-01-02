#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.02 14:08:33

int add(int id){
    cout<<"+ "<<id + 1<<endl;
    int res;cin>>res;
    return res;
}

int sub(){
    cout<<"-"<<endl;
    int res;cin>>res;
    return res;
}

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

vector<int>f;

int find(int x){
    if(f[x]!=x)f[x] = find(f[x]);
    return f[x];
}

void merge(int u, int v)
{
    f[find(v)] = find(u);
}

const int N = 510;

vector<int> ve[N];
void solve()
{
    int n;
    cin >> n;
    f.assign(n, 0);
    iota(f.begin(),f.end(), 0);

    int cnt = 0;
    int sz = 0;
    auto Add = [&](int x)->bool
    {
        int res = add(x);
        int r = res - cnt;
        cnt = res;
        sz++;
        return r;
    };

    auto Sub = [&]()->bool
    {
        int res = sub();
        int r = cnt - res;
        cnt = res;
        sz--;
        return r;
    };

    auto clear = [&]()->void
    {
        while(sz){
            Sub();
        }
        cnt = 0;
        return;
    };

    auto bi = [&](auto&&self, vector<int>a, vector<int>b)->vector<int>
    {
        int m = a.size();
        if(m == 0)return a;
        if(m == 1){
            merge(a[0],b[0]);
            return a;
        }
        shuffle(a.begin(),a.end(), rng);
        vector<int>la, ra, lb, rb;
        for(int i = 0;i < m / 2;i++){
            Add(a[i]);
            la.push_back(a[i]);
        }
        for(int i = 0;i < m;i++){
            int res = Add(b[i]);
            if(res == 1)rb.push_back(b[i]);
            else lb.push_back(b[i]);
        }
        for(int i = m / 2;i < m;i++){
            ra.push_back(a[i]);
        }
        clear();
        self(self, la, lb);
        self(self, ra, rb);
        return a;
    };

    auto cdq = [&](auto&&self, vector<int>v)->vector<int>
    {
        int m = v.size();
        if(m <= 1)return v;
        shuffle(v.begin(),v.end(), rng);
        vector<int>l,r;
        for(int i = 0;i < m;i++){
            if(i < m / 2)l.push_back(v[i]);
            else r.push_back(v[i]);
        }
        l = self(self, l);
        r = self(self, r);
        vector<int>ul, ur, sl, sr;
        for(auto x : l){
            Add(x);
        }
        for(auto x : r){
            int res = Add(x);
            if(res)ur.push_back(x);
            else sr.push_back(x);
        }
        for(auto x : l){
            int res = Sub();
            if(res)ul.push_back(x);
            else sl.push_back(x);
        }
        clear();
        vector<int>ans;
        for(auto x : ul){
            ans.push_back(x);
        }
        for(auto x : ur){
            ans.push_back(x);
        }
        auto res = bi(bi,sl,sr);
        for(auto x : res){
            ans.push_back(x);
        }
        return ans;
    };
    vector<int>xx(n);
    iota(xx.begin(),xx.end(), 0);
    cdq(cdq, xx);


    int ans=0;
    for(int i=0;i<n;i++) ve[find(i)].push_back(i);
    for(int i=0;i<n;i++)
        if(ve[i].size()) ans++;
    cout<<"! "<<ans<<endl;
    for(int i=0;i<n;i++)
        if(ve[i].size())
        {
            cout<<ve[i].size()<<' ';
            for(auto p:ve[i]) cout<<p + 1<<' ';
            cout<<endl;
        }
}

int main()
{
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}