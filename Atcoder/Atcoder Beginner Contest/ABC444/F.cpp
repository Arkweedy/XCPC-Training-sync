#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.07 20:47

void solve()
{
    int n;
    cin >> n;
    i64 m;
    cin >> m;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    i64 h = (n + m) / 2;

    auto calc = [&](int x, int k)->pair<int,int>
    {
        int a = x;
        int b = x;
        int ac = 1, bc = 0;
        //a <= b
        while(ac >= k * 2 && bc >= k * 2){
            int c = a / 2, d = (b + 1) / 2;
            int cc = 0, dc = 0;
            cc += ac;
            dc += bc;
            if((a + 1) / 2 == c)cc += ac;
            else dc += ac;
        }

    };


    auto check = [&](int k)->bool
    {
        //cerr << "check " << k << endl;
        i64 opcnt = 0;
        i64 l = 0, eq = 0, r = 0;
        i64 leq = 0;
        for(int i = 0;i < n;i++){
            // if(a[i] < k)l++;
            // else if(a[i] == k)eq++;
            // else{
            //     i64 v = a[i]; //value of low               
            //     i64 low = 0, high = 0;
            //     i64 cnt = 0;
            //     if(v % 2 == 0)low++;
            //     else high++, v--;
            //     while(1){
            //         if(v / 2 >= k){
            //             if(v % 2 == 1){
            //                 // low -> low + high
            //                 // high -> high + high
            //                 opcnt += low + high;
            //                 i64 nl = low, nh = low + high * 2;
            //                 low = nl;
            //                 high = nh;
            //                 v /= 2;
            //             }
            //             else{
            //                 opcnt += low + high;
            //                 i64 nl = low * 2 + high, nh = high;
            //                 low = nl;
            //                 high = nh;
            //                 v /= 2;
            //             }
            //         }
            //         else{
            //             if(v == 2 * k - 1){
            //                 leq += low;
            //             }
            //             else{
            //                 r += low;
            //             }
            //             // high more divide? 
            //             if((v + 1) / 2 >= k){
            //                 assert(v % 2 == 1);
            //                 int a0 = (v + 1) / 2, a1 = v / 2 + 1;
            //                 if(a0 == 2 * k - 1)leq += high * 2;
            //                 else r += high * 2;
            //                 opcnt += high;
            //             }
            //             else if(v + 1 == 2 * k - 1){
            //                 leq += high;
            //             }
            //             else{
            //                 r += high;
            //             }
            //             break;
            //         }
            //     }
            // }
        }

        //1. leq -> l + eq
        //2. l -> 1
        //2. r -> l + l
        //3. eq -> l + l
        // cerr << m - opcnt << " " << l << ' ' << eq << ' ' << leq << " " << r << endl;
        if(opcnt >= m){
            if(l <= h)return 1;
            else return 0;
        }
        else{
            i64 ned = m - opcnt;
            if(leq >= ned){
                leq -= ned;
                l += ned;
                eq += ned;
                opcnt += ned;
                ned = 0;
            }
            else{
                ned -= leq;
                l += leq;
                eq += leq;
                opcnt += leq;
                leq = 0;
                
            }
            // r -> l + l
            if(ned != 0){
                l += ned;
                ned = 0;
            }
            if(r + eq > h){
                return 1;
            }
            if(l <= h)return 1;
            else return 0;
        }
    };

    int l = 0, r = a.back() + 1;
    while(r - l > 1){
        int m = l + r >> 1;
        if(check(m)){
            l = m;
        }
        else{
            r = m;
        }
    }
    cout << l << endl;
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