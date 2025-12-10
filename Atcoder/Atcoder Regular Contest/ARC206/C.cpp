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
    vector<int>a(n + 1);
    for(int i= 1;i <= n;i++){
        cin>>a[i];
    }
    
    int spos = -1;
    for(int i = 1;i <= n;i++){
        if(a[i] == i){
            spos = i;
            break;
        }
        if(a[i] != -1 && (a[i] <= i - 2 || a[i] >= i + 2)){
            spos = i;
            break;
        }
    }

    if(spos != -1){
        for(int i = 1;i < spos;i++){
            if(a[i] == -1)continue;
            else if(a[i] == i + 1)continue;
            else {
                cout<<0<<endl;
                return;
            }
        }
        for(int i = spos + 1;i <= n;i++){
            if(a[i] == -1)continue;
            else if(a[i] == i - 1)continue;
            else{
                cout<<0<<endl;
                return;
            }
        }
        cout<<1<<endl;
        return;
    }
    else{
        vector<array<Z,3>>dp(n + 1);
        //dp0 : i not connect next, dp1 i connect next, dp2 loop/multi & i not connect next
        //dp0 -> dp1 dp0->dp2
        dp[0][1] = 1;
        for(int i = 1;i <= n;i++){
            if(a[i] == i - 1){
                //dp[i][0] = dp[i - 1][0];
                dp[i][1] = 0;
                dp[i][2] = dp[i - 1][2] + dp[i - 1][1];
                //dp[i][3] = 0;
            }
            else if(a[i] == i + 1){
                //dp[i][0] = 0;
                dp[i][1] = dp[i - 1][1];
                dp[i][2] = 0;
                //dp[i][3] = dp[i - 1][3];
            }
            else if(a[i] == i){
                //dp[i][0] = 0;
                dp[i][1] = 0;
                dp[i][2] = dp[i - 1][1];
                //dp[i][3] = 0;
            }
            else if(a[i] == -1){
                //dp[i][0] = dp[i - 1][0];
                dp[i][1] = dp[i - 1][1];
                dp[i][2] = dp[i - 1][2] + dp[i - 1][1] * (n - 1);
                //dp[i][3] = dp[i - 1][3];
            }
            else{
                //dp[i][0] = 0;
                dp[i][1] = 0;
                dp[i][2] = dp[i - 1][1];
            }
            //cout<<dp[i][0]<<" "<<dp[i][1]<<" "<<dp[i][2]<<endl;
        }
        Z ans = dp[n][2] + dp[n][1];
        cout<<ans<<endl;
    }
    
    return;
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