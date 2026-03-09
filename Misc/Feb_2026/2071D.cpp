#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//2071D.cpp Create time : 2026.02.19 01:21

void solve()
{
    i64 n, l, r;
    cin >> n >> l >> r;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    if(n % 2 == 0){
        int sum = 0;
        for(int i = 1;i <= n / 2;i++){
            sum ^= a[i];
        }
        a.push_back(sum);
        n++;
    }

    vector<int>pa(n + 1);
    for(int i = 1;i <= n;i++){
        pa[i] = pa[i - 1] ^ a[i];
    }
    vector<int>spa(n + 1);
    for(int i = 1;i <= n;i++){
        spa[i] = spa[i - 1] + pa[i];
    }
    vector<int>sa(n + 1);
    for(int i = 1;i <= n;i++){
        sa[i] = sa[i - 1] + a[i];
    }
    

    int s = 0;
    for(int i = 1;i <= n;i++){
        s ^= a[i];
    }

    auto prexor = [&](auto&&self, i64 k)->i64
    {
        if(k <= n){
            return pa[k];
        }
        else{
            if(k % 2 == 1)return s;
            else return s ^ self(self, k / 2);
        }
    };

    auto calc = [&](i64 k)->i64
    {
        return prexor(prexor, k) ^ prexor(prexor, k - 1);
    };

    auto prexorsum = [&](auto&&self, i64 k)->i64 //[1, k]
    {
        if(k <= n){
            return spa[k];
        }
        else{
            i64 res = spa[n];
            if(k % 2 == 0){
                //cerr << prexor(prexor, k) << endl;
                res += prexor(prexor, k);
                k--;
            }
            res += (k - n) / 2 * s;
            if(s == 0){
                res += self(self, k / 2) - self(self, n / 2);
            }
            else{
                res += (k / 2 - (n + 1) / 2 + 1) - (self(self, k / 2) - self(self, n / 2));
            }
            return res;
        }
    };

    auto presum = [&](i64 k)->i64 //[1, k]
    {
        if(k <= n){
            return sa[k];
        }
        else{
            i64 res = 0;
            if(k % 2 == 0){
                res += calc(k);
                k--;
            }
            res += sa[n];
            res += 2 * (prexorsum(prexorsum, k / 2) - prexorsum(prexorsum, n / 2));
            return res;
        }
    };
    cout << presum(r) - presum(l - 1) << endl;
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