#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr istream &operator>>(istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};
//template<>
//int MInt<0>::Mod = 998244353;
//int MInt<0>::Mod = 1000000007;
constexpr int P = 998244353;
//constexpr int P = 1000000007;
using Z = MInt<P>;

void solve()
{
    int n;
    cin>>n;
    vector<Z>dp(n + 1);
    //vector<vector<int>>invalid(n + 1);
    
    vector<vector<vector<int>>>vs(n + 1,vector<vector<int>>(n + 1, vector<int>(n + 1)));//begin at i, len j, first is k
    vector<vector<int>>trans(n + 1,vector<int>(n + 1));//todo
    for(int i = 0;i < n;i++){
        for(int j = i + 1;j <= n;j++){
            trans[i][j] = j - i;
        }
    }

    
    //0~n-1 -> 1~n cases
    int m;
    cin>> m;
    for(int i = 0;i < m;i++){
        int p, x;
        cin>>p>>x;
        //invalid[p].push_back(x);
        for(int j = x;j <= n;j++){//len
            for(int k = p - 1;k >= max(0,p - j);k--){//start
                //start = k, len = j, a[p] = x
                int dis = p - k - 1;
                int fir = ((x - dis) > 0 ? x - dis : x - dis + j);
                if(!vs[k][j][fir]){
                    vs[k][j][fir] = 1;
                    trans[k][k + j]--;
                }
            }
        }
    }

    // for(int i = 0;i < n;i++){
    //     for(int j = 1;j <= n;j++){
    //         for(int k = 1;k <= n;k++){
    //             if(vs[i][j][k]){
    //                 cerr<<"vs : "<<i<<" -> "<<j<<" fir = "<<k<<endl;
    //             }
    //         }
    //     }
    // }

    vector<vector<int>>dec(n + 1,vector<int>(n + 1));
    auto ntrans = trans;
    for(int i = 0;i < n;i++){//start
        for(int j = 1;j * 2 + 1 + i <= n;j++){
            //cerr<<"try "<<i<<" "<<i + j * 2 + 1<<endl;
            //cerr<<i<<" "<<i + j + 1<<" "<<j + 1<<endl;
            //cerr<<vs[i][j + 1][1]<<endl;
            //cerr<<vs[i + j + 1][i + j * 2 + 1][j + 1]<<endl;
            if(!vs[i][j + 1][1] && !vs[i + j][i + j * 2 + 1][j + 1]){
                ntrans[i][i + j * 2 + 1]--;
                //cerr<<i<<" "<<i + j * 2 + 1 <<"is sub"<<endl;
            }
        }
    }

    // cerr<<"trans:"<<endl;
    // for(int i = 0;i < n;i++){
    //     for(int j =0;j <= n;j++){
    //         cerr<<trans[i][j]<<" ";
    //     }
    //     cerr<<endl;
    // }
    // cerr<<"ntrans:"<<endl;
    // for(int i = 0;i < n;i++){
    //     for(int j =0;j <= n;j++){
    //         cerr<<ntrans[i][j]<<" ";
    //     }
    //     cerr<<endl;
    // }

    //cerr<<"dp : "<<endl;
    dp[0] = 1;
    Z ans = 0;
    for(int i = 0;i < n;i++){
        for(int j = i + 1;j <= n;j++){
            dp[j] += dp[i] * ntrans[i][j];
        }
    }
    for(int i = 0;i <= n;i++){
        cerr<<dp[i]<<" ";
    }
    cerr<<endl;
    // for(int i = 0;i < n;i++){
    //     vector<Z>ndp(n + 1);
    //     if(i == 0){
    //         for(int j = 0;j < n;j++){//dp[j]->
    //             for(int k = j + 1;k <= n;k++){//dp[k]
    //                 ndp[k] += dp[j] * trans[j][k];
    //             }
    //         }
    //     }
    //     else{
    //          for(int j = 0;j < n;j++){//dp[j]->
    //             for(int k = j + 1;k <= n;k++){//dp[k]
    //                 ndp[k] += dp[j] * ntrans[j][k];
    //             }
    //         }
    //     }
    //     dp = move(ndp);
    //     ans += dp[n];
    //     for(int i = 0;i <= n;i++){
    //         cerr<<dp[i]<<" ";
    //     }
    //     cerr<<endl;
    // }
    cout<<dp[n]<<endl;
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