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

struct trie{
    static const int N = 1000;//pool
    static const int n = 10;//range 
    int tree[N][n] = { 0 };
    int cnt[N] = { 0 };
    int tot = 1;

public:
    int to_num(char c)
    {
        return c - '0';
    }

    int insert(string s, int root = 0, int pos = 0)
    {
        int x = to_num(s[pos]);
        if (tree[root][x] == 0) {
            tree[root][x] = tot++;
        }
        cnt[tree[root][x]]++;
        if (pos + 1 != s.size()) {
            return insert(s, tree[root][x], pos + 1);
        }
        else{
            return pos;
        }
    }

    int query(string& s, int root = 0, int pos = 0)
    {
        if (pos == s.size())return cnt[root];
        int x = to_num(s[pos]);
        if (tree[root][x] == 0)return 0;
        else return query(s, tree[root][x], pos + 1);
    }

    void clear()
    {
        for (int i = 0; i <= tot; i++) {
            for (int j = 0; j < n; j++) {
                tree[i][j] = 0;
            }
            cnt[i] = 0;
        }
        tot = 1;
    }
};

struct Comb {
    int n;
    vector<Z> _fac;
    vector<Z> _invfac;
    vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }

    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
        
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<Z>years(n);
    vector<int>prez(n);
    for(int i = 0;i < n;i++){
        prez[i] = (s[i] == '0' ? 1 : 0);
    } 
    for(int i = 1;i < n;i++){
        prez[i] += prez[i - 1];
    }
    for(int i = 0;i < n;i++){
        years[i] = comb.binom(i + 1, 4) - comb.binom(prez[i], 4);
    }

    vector<Z>y4(n);// mod4 = 0,1,2,3
    vector<Z>y100(n);// xx 00
    vector<Z>y400(n);// xx 00
    vector<array<array<Z,4>,5>>yr4(n + 1);//len =0,1,2,3,4 mod4 = 0,1,2,3
   
    yr4[0][0][0] = 1;
    for(int i = 1;i <= n;i++){
        int x = s[i - 1] - '0';
        for(int j = 1;j <= 4;j++){//len
            for(int k = 0;k < 4;k++){//mod
                yr4[i][j][(k * 10 + x) % 4] += yr4[i - 1][j - 1][k];
            }
        }
    }
    for(int i = 0;i < n;i++){
        y4[i] = yr4[i + 1][4][0] - yr4[i][4][0];
    }
    auto calc = [&](vector<Z>&sum,int x)->void
    {
        vector<array<Z,5>>y(n + 1);// idx, len
        y[0][0] = 1;
        array<int,5>digit = {0, x % 10,x / 10 % 10, x / 100 % 10, x / 1000};
        for(int i = 1;i <= n;i++){
            int d = s[i - 1] - '0';
            y[i] = y[i - 1];
            for(int j = 1;j <= 4;j++){
                if(d == digit[j]){
                    y[i][j] += y[i - 1][j - 1];
                }
            }
        }
        for(int i = 0;i < n;i++){
            sum[i] += (y[i + 1][4] - y[i][4]);
        }
    };

    for(int i = 100;i <= 9999;i+=100){
        calc(y100,i);
    }
    for(int i =400;i <= 9999;i+=400){
        calc(y400,i);
    }

    //pre calc trans
    auto calc_date = [&](int x)->int
    {
        for(int i = 0;i < n;i++){
            
        }
    };
   
    trie tri;
    vector<int>endpos;
    int endrun = 0;
    for(int i = 1;i <= 366;i++){
        string x = to_string(calc_date(i));
        while(x.length() < 4)x = '0' + x;
        endpos.push_back(tri.insert(x));
    }
    endrun = tri.insert(string("0229"));
    cerr<<"ok"<<endl;
    auto &t = tri.tree;
    int m = tri.tot;
    vector<Z>cnt(m);
    vector<Z>all(n);
    vector<Z>run(n);
    cnt[0] = 1;
    for(int i = n - 1;i >= 0;i--){
        int x = s[i] - '0';
        for(int j = m - 1;j >= 0;j--){
            if(t[j][x]){
                cnt[t[j][x]] += cnt[j];
            }
        }
        for(auto e : endpos){
            all[i] += cnt[e];   
        }
        all[i] -= cnt[endrun];
        run[i] = cnt[endrun];
    }


    Z ans = 0;
    for(int i = 0;i < n - 1;i++){
        ans += years[i] * all[i + 1];
        ans += (y4[i] - y100[i] + y400[i]) * run[i + 1];
        cerr<<years[i]<<" "<<y4[i]<<" "<<y100[i]<<" "<<y400[i]<<endl;
        cerr<<all[i + 1]<<" "<<run[i + 1]<<endl;
    }

    cout<<ans<<endl;
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