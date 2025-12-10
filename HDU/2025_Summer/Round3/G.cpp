#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>l(n),r(n);
    vector<ull>h(n);
    mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
    for(int i = 0;i < n;i++){
        cin>>l[i]>>r[i];
        r[i]++;
        h[i] = g();
    }
    vector<int>lid(n),rid(n);
    iota(lid.begin(),lid.end(),0);
    iota(rid.begin(),rid.end(),0);
    sort(lid.begin(),lid.end(),[&](int i, int j)->bool
    {
        return l[i] < l[j];
    });
    sort(rid.begin(),rid.end(),[&](int i, int j)->bool
    {
        return r[i] < r[j];
    });
    set<ull>st;
    ull ha = 0;
    int pl = 0,pr = 0;
    int p = -1;
    st.insert(0);
    while(pl < n || pr < n){
        if(pl == n)p = r[rid[pr]];
        else p = min(l[lid[pl]],r[rid[pr]]);
        while(pl < n && l[lid[pl]] == p){
            ha ^= h[lid[pl]];
            pl++;
        }
        while(pr < n && r[rid[pr]] == p){
            ha ^= h[rid[pr]];
            pr++;
        }
        st.insert(ha);
    }
    cout<<st.size()<<endl;
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