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

    void late_init(vector<T>& arr)
    {
        n = arr.size();
        len = floor(log2l(n)) + 1;
        stt.resize(n, vector<T>(len));

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
        if(l > r)return 1145140;
        int k = floor(log2(r - l + 1));// range_len == r - l + 1
        return choose(stt[l][k], stt[r - (1 << k) + 1][k]);
    }
};


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
    }
    a.push_back(0);

    vector<int>samax(n + 1, 0);
    for(int i = n - 1;i >= 0;i--){
        samax[i] = max(a[i],samax[i + 1]);
    }

    rmq<int,false>mia(a);

    // int len = ceil(log2(n + 1));
    // vector<vector<int>>st(n + 1,vector<int>(len));
    // for(int i = 0;i <= n;i++){
    //     st[i][0] = a[i];
    // }
    // for(int k = 1;k < len;k++){
    //     for(int i = 0;i + (1 << k) - 1 <= n;i++){
    //         st[i][k] = min(st[i][k - 1] , st[i + (1 << k - 1)][k - 1]);
    //     }
    // }
    
    // auto range_min = [&](int l, int r)->int
    // {
    //     int k = floor(log2(r - l + 1));
    //     return min(st[l][k], st[r - (1 << k) + 1][k]);
    // };
    
    int lp = 0, rp = 0;
    int ans = 0;
    for(int i = 0;i < n;i++){
        int last = 0;
        while(lp + rp <= n && rp <= i){
            if(a[lp] < b[rp]){
                last = 1;
                rp++;
            }else{
                lp++;
            }
        }
        if(!last)lp--;
        ans = max(ans, lp);
        if(rp > i){
            
            int maxl = lp;
            if(lp + 1 <= n && samax[lp + 1] > b[rp - 1]){
                maxl++;
                int l = lp, r = n - rp + 1;
                while(r - l > 1){
                    int m = l + r >> 1;
                    if(mia.qry(maxl, m) > b[rp - 1] && samax[m + 1] > b[rp - 1]){
                        l = m;
                    }else{
                        r = m;
                    }
                }
                ans = max(ans, l + 1);
            }
        }else{
            break;
        }
    }
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