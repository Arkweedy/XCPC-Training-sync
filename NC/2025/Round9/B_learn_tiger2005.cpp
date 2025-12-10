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
    constexpr int N = 5000;
    array<array<int,10>,N>next{};
    array<int,N>len;
    array<int,N>id;
    len.fill(0);
    id.fill(-1);
    constexpr int root = 1, croot = 2, lroot = 3, end = 4;
    len[croot] = len[lroot] = 4;//dep
    len[end] = 8;
    int tot = end + 1;
    array<int,4>D ={1000,100,10,1};
    auto insert = [&](int x, int root, int end = -1)->void
    {
        int p = root;
        for(int i = 0;i < 4;i++){
            int s = x / D[i] % 10;
            if(i == 3 && end != -1){//
                next[p][s] = end;
            }
            else if(next[p][s] == 0){
                assert(tot < N);
                next[p][s] = tot++;
                len[next[p][s]] = len[p] + 1;
            }
            p = next[p][s];
        }
        return;
    };
    vector<int>days = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    for(int i = 1;i <= 12;i++){
        for(int j = 1;j <= days[i];j++){
            insert(i * 100 + j, lroot, end);
            insert(i * 100 + j, croot, end);
        }
    }
    insert(229,lroot,end);

    for(int i = 1;i <= 9999;i++){
        int isleap = 0;
        if(i % 4 == 0)isleap = 1;
        if(i % 100 == 0)isleap = 0;
        if(i % 400 == 0)isleap = 1;
        if(isleap)insert(i,root,lroot);
        else insert(i,root,croot);
    }

    map<array<int,10>,int>mp;
    auto hopcroft = [&]()->void
    {
        for(int d = 8;d >= 0;d--){//len
            for(int i = 1;i < tot;i++){//merge
                if(len[i] == d){
                    if(!mp.count(next[i])){
                        mp[next[i]] = i;
                    }
                    else{
                        id[i] = mp[next[i]];
                    }
                }
            }
            for(int i = 1;i < tot;i++){//update
                if(len[i] == d - 1){
                    for(int j = 0;j < 10;j++){
                        if(next[i][j] && id[next[i][j]] != -1){
                            next[i][j] = id[next[i][j]];
                        }
                    }
                }
            }
        }
    };
    
    hopcroft();
    cerr<<tot<<" "<<mp.size()<<endl;

    int xx = 1;
    vector<int>idx(N, 0);
    for(int d = 0;d <= 8;d++){
        for(auto [trans, p] : mp){
            if(len[p] == d){
                idx[p] = xx++;
            }
        }
    }

    cerr<<idx[root]<<endl;
    cerr<<idx[lroot]<<" "<<idx[croot]<<endl;
    cerr<<idx[end]<<endl;
    for(int k = 1;k <= 26;k++){//output by order
        for(auto [trans , p] : mp){
            if(idx[p] == k){
                cerr<<idx[p]<<" ";
                cerr<<"{ ";
                for(int i = 0;i < 10;i++){
                    cerr<<idx[trans[i]]<<", "[i == 9];
                }
                cerr<<"};"<<endl;
            }
        }
    }
    
    array<vector<int>, 10>tr;
    map<int,int>nid;
    for(int i = 1;i < tot;i++){
        if(id[i] == -1){
            cerr<<i<<" "<<idx[i]<<endl;
            for(int j = 0;j < 10;j++){
                if(next[i][j]){
                    tr[j].push_back(i);
                }
            }
        }
    }
    

    for(int k = 0;k < 10;k++){
        sort(tr[k].begin(),tr[k].end(),[&](int i, int j)->bool
        {
            return len[i] > len[j];       
        });
    }

    int n;
    string s;
    cin>>n>>s;
    vector<Z>cnt(N);
    cnt[root] = 1;
    for(auto ch : s){
        int x = ch - '0';
        //cerr<<"tran "<<x<<endl;
        for(auto p : tr[x]){
            //cerr<<p<<" -> "<<next[p][x]<<endl;
            cnt[next[p][x]] += cnt[p];
        }
    }

    cout<<cnt[end]<<endl;
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