#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template <typename T, bool isMaxQuery>//if 1 base, set arr[0] to inf / -inf . std::max/min override
class rmq
{
    int n;//array length
    int len;//st table length
    vector<vector<T>>stt;//st_table

    T choose(const T& a, const T& b)const
    {
        if constexpr (isMaxQuery) {
            return std::max(a, b);
        }
        else {
            return std::min(a, b);
        }
    }

    void build(vector<T>& arr)
    {
        //build
        for (int i = 0; i < n; i++) {
            stt[i][0] = arr[i];
        }
        for (int k = 1; k < len; k++) {
            for (int i = 0; i + (1 << k) - 1 < n; i++) {
                stt[i][k] = choose(stt[i][k - 1], stt[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

public:
    rmq() = default;

    void init(vector<T>& arr)
    {
        n = arr.size();
        len = floor(log2l(n)) + 1;
        stt.assign(n, vector<T>(len));
        build(arr);
    }

    rmq(vector<T>& arr)
    {
        n = arr.size();
        len = floor(log2l(n)) + 1;
        stt.resize(n, vector<T>(len));
        build(arr);
    }

    T qry(int l, int r)
    {
        int k = floor(log2(r - l + 1));// range_len == r - l + 1
        return choose(stt[l][k], stt[r - (1 << k) + 1][k]);
    }
};


void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
        a[i] = (a[i] > k ? -1 : 1);
    }

    vector<int>pre(n + 1),suf(n + 2);
    for(int i = 1;i <= n;i++){
        pre[i] = pre[i - 1] + a[i];
    }
    for(int i = n;i >= 1;i--){
        suf[i] = suf[i + 1] + a[i];
    }
    
    rmq<int,true>pm(pre),sm(suf);

    for(int i = 1;i <= n;i++){
        if(pre[i] >= 0 && i <= n - 2 && (sm.qry(i + 1,n) >= 0 || pm.qry(i + 1, n) >= pre[i])){
            //cerr<<"ok at "<<i<<endl;
            cout<<"Yes"<<endl;
            return;
        }
        if(suf[i] >= 0 && i >= 2 && (pm.qry(1,i - 1) >= 0 || sm.qry(1,i - 1) >= suf[i])){
            //cerr<<"ko at "<<i<<endl;
            cout<<"Yes"<<endl;
            return;
        }
    }
    cout<<"No"<<endl;
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