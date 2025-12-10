#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int ALPHA_SIZE = 26;
struct PAM
{
    struct Node{
        array<int,ALPHA_SIZE>next;
        int dep;//length of palindrome suffix link list
        int len;//length
        int cnt;//cnt as a ps
        int fail;//id of lps
        int diff;
        int slink;
        Node():next{},dep{},len{},cnt{1},fail{},diff{},slink{}{}
    };

    static constexpr int odd_root = 0;
    static constexpr int even_root = 1;
    //odd root -> 0
    //even root -> 1

    vector<Node>t;
    int suff;
    string s;

    PAM()
    {
        init();
    }

    PAM(string &s)
    {
        init();
        for(auto ch : s){
            add(ch);
        }
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[1].slink = 0;
        t[1].diff = 1;
        suff = 1;
        s.clear();
    }

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    constexpr int num(const char& c)noexcept
    {
        return c - 'a';
    };

    bool add(char c)
    {
        s += c;
        int x = num(c);
        int cur = get_fail(suff);
        if(t[cur].next[x]){//exist
            suff = t[cur].next[x];
            t[suff].cnt++;
            return false;
        }

        int p = newNode();
        suff = p;//new longest palindrome suffix 
        t[p].len = t[cur].len + 2;
        t[cur].next[x] = p;
        if(t[p].len == 1){//trans form odd_root
            t[p].fail = even_root;//even root
            t[p].dep = 1;
            t[p].diff = 1;
            t[p].slink = 1;//even_root
            return true;
        }
        int f = get_fail(t[cur].fail);// find new fail begin at lps(cur)
        t[p].fail = t[f].next[x];
        t[p].dep = t[t[p].fail].dep + 1;
        t[p].diff = t[p].len - t[t[p].fail].len;
        if(t[p].diff == t[t[p].fail].diff)t[p].slink = t[t[p].fail].slink;
        else t[p].slink = t[p].fail;
        return true;
    }

    int get_fail(int p)
    {
        // if p == odd_root -> len = -1, ok
        int len = s.length() - 1;
        while(len - t[p].len - 1 < 0 || s[len] != s[len - t[p].len - 1])p = t[p].fail; 
        return p;
    }

    void calc_cnt()
    {
        for(int i = t.size() - 1;i > 1;i--){
            t[t[i].fail].cnt += t[i].cnt;
        }
    }
};

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
//constexpr int P = 998244353;
constexpr int P = 1000000007;
using Z = MInt<P>;

void solve()
{
    string s;
    cin>>s;
    int n = s.length();
    string ss;
    for(int i = 0;i < n / 2;i++){
        ss += s[i];
        ss += s[n - i - 1];
    }
    s = ss;
    //cerr<<s<<endl;
    PAM pam;
    auto &t = pam.t;
    auto &end = pam.suff;
    vector<Z>dp(n + 3);
    vector<Z>sdp(n + 5);
    dp[0] = 1;
    for(int i = 0;i < n;i++){
        pam.add(s[i]);
        int p = end;
       
        while(p != 1){
            //cerr<<p<<" "<<t[p].slink<<" "<<i + 1 - t[t[p].slink].len - t[p].diff<<endl;
            //cerr<<t[p].fail<<endl;
            sdp[p] = dp[i + 1 - t[t[p].slink].len - t[p].diff];
            if(t[p].fail != t[p].slink)sdp[p] += sdp[t[p].fail];
            dp[i + 1] += sdp[p];
            //cerr<<"dp = "<<dp[i + 1]<<endl;
            p = t[p].slink;
        }
        if(i % 2 == 0)dp[i + 1] = 0;
    }
    // for(int i = 0;i <= n;i++){
    //     cerr<<dp[i]<<" ";
    // }
    //cerr<<endl;
    cout<<dp[n]<<endl;
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