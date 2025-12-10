#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int M = 52;//size 
constexpr int V = M + 1;
struct SAM
{
    struct Node{
        int len;
        int link;
        array<int,M>nxt;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;
    vector<vector<int>>ot;
    vector<int>endpos_size;
    
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
        if(islower(x))return x - 'a';
        else return x - 'A' + 26;
        //return x - 'a';
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
        //get_out_linktree();
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

    void calc_endpos_size(string &s)
    {
        endpos_size.resize(t.size());
        int p = 1;
        for(auto c:s){
            p = t[p].nxt[num(c)];
            endpos_size[p]++;
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                endpos_size[p] += endpos_size[s];
            }
        };
        dfs(dfs,1);
        endpos_size[1] = 1;
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


using matrix = array<array<Z,V>,V>;

matrix operator*(const matrix& lhs, const matrix& rhs)
{
    matrix res{};
    for(int i = 0;i < V;i++){
        for(int j = 0;j < V;j++){
            for(int k = 0;k < V;k++){
                res[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return res;
}

matrix get_diag(int x)
{
    matrix m;
    for(int i = 0;i < V;i++){
        m[i][i] = x;
    }
    return m;
}

template<typename T>
array<T, V> operator+(const array<T,V>&lhs, const array<T,V>&rhs)
{
    array<T,V>res{};
    for(int i = 0;i < V;i++){
        res[i] = lhs[i] + rhs[i];
    }
    return res;
}

template<typename T>
array<T, V>& operator+=(array<T,V>&lhs, const array<T,V>&rhs)
{
    for(int i = 0;i < V;i++){
        lhs[i] += rhs[i];
    }
    return lhs;
}

void print(matrix m)
{
    for(int i = 0;i < V;i++){
        for(int j = 0;j < V;j++){
            cerr<<m[i][j]<<" ";
        }
        cerr<<endl;
    }
    cerr<<endl;
}

// 3 0 3 
// 2 1 2 
// 0 0 1 

// 3 1 3 
// 2 1 2 
// 0 0 1 

void solve()
{
    int n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    SAM sam(s);
    auto &t = sam.t;
    int m = t.size();
    matrix tr;
    tr[V - 1][V - 1] = 1;

    //tr[i][j] -> begin is i, can link j ?

    //vector<ll>scnt(m, 1);
    vector<array<ll,V>>cnt(m);
    vector<int>vs(m);
    auto dfs = [&](auto&&self, int p)->void
    {
        if(vs[p])return;
        vs[p] = true;
        cnt[p][V - 1] = 1;//initial 
        for(int i = 0;i < M;i++){
            int s = t[p].nxt[i];
            if(s){                
                self(self, s);
                cnt[p] += cnt[s]; //recalc
            }
            else{
                cnt[p][i]++;// ? 
            }
        }
    };
    dfs(dfs, 1);


    for(int i = 0;i < M;i++){
        int p = t[1].nxt[i];
        if(p){
            for(int j = 0;j < V;j++){
                tr[i][j] = cnt[p][j];
            }
        }
    }

    //print(tr);

    // vector<array<int,V>>cnt(m);
    // vector<int>indeg(m);
    // for(int i = 1;i < m;i++){
    //     for(int j = 0;j < M;j++){
    //         if(t[i].nxt[j] != 0){
    //             indeg[t[i].nxt[j]]++;
    //         }
    //     }
    // }
    // for(int i = 0;i < M;i++){
    //     if(t[1].nxt[i] != 0)
    //         cnt[t[1].nxt[i]][i]++;
    // }
    // queue<int>q;
    // q.push(1);
    // while(!q.empty()){
    //     int p = q.front();
    //     q.pop();
    //     for(int i = 0;i < M;i++){
            
    //         int s = t[p].nxt[i];//first cases
    //         if(s){
    //             cnt[s] += cnt[p];
    //             indeg[s]--;
    //             if(indeg[s] == 0)q.push(s);
    //         }
    //         else{
    //             for(int j = 0;j < M;j++){//O(nV^2)
    //                 tr[j][i] += cnt[p][j];
    //             }
    //         }
    //     }
    //     for(int j = 0;j < M;j++){
    //         tr[j][V - 1] += cnt[p][j];
    //     }
    // }
    // print(tr);


    //matrix res = get_diag(1);
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    const int pi = g() % V;
    vector<int>row(V),col(V);
    iota(row.begin(),row.end(),0);
    iota(col.begin(),col.end(),0);
    shuffle(row.begin(),row.end(),g);
    shuffle(col.begin(),col.end(),g);
    matrix res{};
    for(int i = 0;i < V;i++){
        res[row[i]][col[i]] = 1; //correct
        //res[g() % V][col[i]] = 1; //correct
        //res[row[i]][g() % V] = 1; //wrong,can not assure col
    }

    // print(tr);
    // print(res);

    while(k){
        if(k & 1)res = res * tr;
        tr = tr * tr;
        k >>= 1;
    }

    //print(res);

    Z ans = 0;
    //ans = res[pi][V - 1];
    for(int i = 0;i < V;i++){
        ans += res[i][V - 1];
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