#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct SAM
{
    static constexpr int M = 26;//size 
    struct Node{
        int len;
        int link;
        array<int,M>nxt;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;
    vector<vector<int>>ot;
    vector<int>endpos_cnt;
    vector<ll>string_dif_cnt;
    vector<ll>string_all_cnt;
    int last = 1;

    SAM(){
        init();
    }

    SAM(string& s){
        init();
        build(s);
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[0].nxt.fill(1);
    }

    int newNode()
    {
        t.push_back(Node());
        return t.size() - 1;
    }

    static inline int num(int x)
    {
        return x - 'a';
    }

    void extend(int x)
    {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while(p != 0 && t[p].nxt[x] == 0){
            t[p].nxt[x] = cur;
            p = t[p].link;
        }
        int q = t[p].nxt[x];
        if(p == 0){
            t[cur].link = 1; 
        }
        else if(t[q].len == t[p].len + 1){
            t[cur].link = q;
        }
        else{
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone].nxt = t[q].nxt;
            t[clone].len = t[p].len + 1;
            t[cur].link = clone;
            t[q].link = clone;
            while(p != 0 && t[p].nxt[x] == q){
                t[p].nxt[x] = clone;
                p = t[p].link;
            }
        }
        last = cur;
        return;
    }

    void build(string& s)
    {
        for(auto &c : s){
            extend(num(c));
        }
        get_out_linktree();
    }

    inline int nxt(int p, int x)
    {
        return t[p].nxt[x];
    }

    void get_out_linktree()
    {
        ot.resize(t.size());
        for(int i = 2;i < t.size();i++){
            ot[t[i].link].push_back(i);
        }
    }

    void calc_endpos_cnt(string &s)
    {
        endpos_cnt.resize(t.size());
        int p = 1;
        for(auto c:s){
            p = t[p].nxt[num(c)];
            endpos_cnt[p]++;
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                endpos_cnt[p] += endpos_cnt[s];
            }
        };
        dfs(dfs,1);
        endpos_cnt[1] = 1;
    }

    void calc_dif_string_cnt()
    {
        string_dif_cnt.assign(t.size(),1);
        vector<int>outdeg(t.size());
        vector<vector<int>>ig(t.size());//inner dag
        queue<int>q;
        for(int i = 1;i <t.size();i++){
            outdeg[i] = M - count(t[i].nxt.begin(),t[i].nxt.end(),0);
            if(outdeg[i] == 0)q.push(i);
            for(int j = 0;j < M;j++){
                if(t[i].nxt[j] != 0){
                    ig[nxt(i,j)].push_back(i);
                }
            }
        }
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : ig[p]){
                string_dif_cnt[s] += string_dif_cnt[p];
                outdeg[s]--;
                if(outdeg[s] == 0)q.push(s);
            }
        }
        return;
    }

    void calc_all_string_cnt()
    {
        string_all_cnt.resize(endpos_cnt.size());
        for(int i = 0;i < t.size();i++){
            string_all_cnt[i] = endpos_cnt[i];
        }
        //transform(endpos_cnt.begin(),endpos_cnt.end(),string_all_cnt.begin(),std::_Identity<int>());
        vector<int>outdeg(t.size());
        vector<vector<int>>ig(t.size());//inner dag
        queue<int>q;
        for(int i = 1;i <t.size();i++){
            outdeg[i] = M - count(t[i].nxt.begin(),t[i].nxt.end(),0);
            if(outdeg[i] == 0)q.push(i);
            for(int j = 0;j < M;j++){
                if(t[i].nxt[j] != 0){
                    ig[nxt(i,j)].push_back(i);
                }
            }
        }
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : ig[p]){
                string_all_cnt[s] += string_all_cnt[p];
                outdeg[s]--;
                if(outdeg[s] == 0)q.push(s);
            }
        }
        return;
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
constexpr int P = 998244353;
//constexpr int P = 1000000007;
using Z = MInt<P>;

using matrix = array<Z,4>;

matrix operator+ (const matrix& lhs, const matrix& rhs)
{
    matrix res{}
    for(int i = 0;i < 4;i++){
        res[i] = lhs[i] + rhs[i];
    }
    return res;
}

matrix operator* (const matrix& lhs, const matrix& rhs)
{
    matrix res{}
    res[0] = lhs[0] * rhs[0] + lhs[1] * rhs[2];
    res[1] = lhs[0] * rhs[1] + lhs[1] * rhs[3];
    res[2] = lhs[2] * rhs[0] + lhs[3] * rhs[2];
    res[3] = lhs[2] * rhs[1] + lhs[3] * rhs[3];
    return res;
}

template <typename T>
struct Fenwick {
    int n;
    vector<T> a;

    Fenwick(int n_ = 0) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    
    //[0,x)
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
	
		//[l,r)
    T query(int l, int r) {
        return sum(r) - sum(l);
    }

    //返回 sum(x) 小于等于 k 的最大的 x
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};




void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    SAM sam(s);
    sam.calc_endpos_cnt();
    auto &t = sam.t;
    auto &ot = sam.ot;
    vector<vector<int>>endset(t.size());
    vector<Fenwick<matrix>>fen(t.size());
    int p = 1;
    for(int i = 1; i <= n;i++){
        p = t[p].nxt[s[i] - 'a'];
        endset[p].push_back(i);
        fen[p].
    }

    matrix D = {1,3,1,0};
    matrix iD = {0,1,Z(1)/3, Z(-1)/3};

    int m = t.size();
    vector<int>fa(m),sz(m,1),hson(m,-1);
    auto dfs1 = [&](auto&&self, int p)->void
    {
        for(auto s : ot[p]){
            fa[s] = p;
            self(self, s);
            sz[p] += sz[s];
            if(hson[p] == -1 || sz[hson[p]] < sz[s]){
                hson[p] = s;
            }
        }
    };


    
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