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

constexpr size_t L = 12;

using matrix = array<array<Z,L>,L>;
constexpr matrix O{};

matrix operator*(const matrix& lhs, const matrix& rhs)
{
    if(lhs == O || rhs == O)return O;
    matrix res{};
    for(int i = 0;i < L;i++){
        for(int j = 0;j < L;j++){
            for(int k = 0;k < L;k++){
                res[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return res;
}

matrix& operator+=(matrix& lhs, const matrix& rhs)
{
    for(int i = 0;i < L;i++){
        for(int j = 0;j < L;j++){
            lhs[i][j] += rhs[i][j];
        }
    }
    return lhs;
}

matrix get_diag(int x)
{
    matrix m;
    for(int i = 0;i < L;i++){
        m[i][i] = x;
    }
    return m;
}

using Matrix = array<array<matrix, L>, L>;




Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
    Matrix res{};
    for(int i = 0;i < L;i++){
        for(int j = 0;j < L;j++){
            for(int k = 0;k < L;k++){
                res[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return res;
}


void solve()
{
    Matrix A{};
    A[0][0] =   {1,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0};
    A[0][1] =   {0,0,0,0,0,0,0,0,0,0,0,0,
                0,1,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,};
    A[0][2] =   {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,2,0,0,0,0,0,0,0,0,0,0,
                0,0,1,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0};
    A[0][3] =   {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,3,1,0,0,0,0,0,0,0,0,0,
                0,1,4,0,0,0,0,0,0,0,0,0,
                0,0,3,0,0,0,0,0,0,0,0,0,
                0,0,0,1,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,};
    A[0][4] = {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,4,4,0,0,0,0,0,0,0,0,0,
                0,2,12,2,0,0,0,0,0,0,0,0,
                0,2,12,4,0,0,0,0,0,0,0,0,
                0,0,9,6,0,0,0,0,0,0,0,0,
                0,0,3,6,0,0,0,0,0,0,0,0,
                0,0,0,4,0,0,0,0,0,0,0,0,
                0,0,0,0,1,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0};
    A[0][5] = {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,5,10,1,0,0,0,0,0,0,0,0,
                0,3,28,13,0,0,0,0,0,0,0,0,
                0,4,35,29,1,0,0,0,0,0,0,0,
                0,3,35,41,4,0,0,0,0,0,0,0,
                0,1,30,44,7,0,0,0,0,0,0,0,
                0,0,17,45,7,0,0,0,0,0,0,0,
                0,0,8,30,11,0,0,0,0,0,0,0};
    A[0][6] = {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,6,20,6,0,0,0,0,0,0,0,0,
                0,4,55,50,3,0,0,0,0,0,0,0,
                0,6,80,118,18,0,0,0,0,0,0,0,
                0,6,95,186,48,0,0,0,0,0,0,0,
                0,6,101,230,85,2,0,0,0,0,0,0,
                0,2,94,260,113,4,0,0,0,0,0,0};
    A[0][7] = {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,7,35,21,1,0,0,0,0,0,0,0,
                0,5,96,145,26,0,0,0,0,0,0,0,
                0,8,155,358,124,3,0,0,0,0,0,0,
                0,9,207,616,313,16,0,0,0,0,0,0,
                0,11,250,859,567,53,0,0,0,0,0,0};
    A[0][8] = {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,8,56,56,8,0,0,0,0,0,0,0,
                0,6,154,350,126,4,0,0,0,0,0,0,
                0,10,268,898,552,48,0,0,0,0,0,0,
                0,12,389,1654,1404,204,1,0,0,0,0,0};
    A[0][9] = {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,9,84,126,36,1,0,0,0,0,0,0,
                0,7,232,742,448,43,0,0,0,0,0,0,
                0,12,427,1967,1887,357,6,0,0,0,0,0};
    A[0][10] = {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,10,120,252,120,10,0,0,0,0,0,0,
                0,8,333,1428,1302,252,5,0,0,0,0,0};
    A[0][11] = {0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,0,0,
                0,11,165,462,330,55,1,0,0,0,0,0};

    vector<Matrix>BA(30);
    BA[0] = A;
    for(int i = 1;i < 30;i++){
        BA[i] = BA[i - 1] * BA[i - 1];
    }

    auto print = [&](matrix m)->void
    {
        for(int i = 0;i < L;i++){
            for(int j = 0;j < L;j++){
                cerr<<m[i][j]<<" ";
            }
            cerr<<endl;
        }
        cerr<<endl;
    };

    print(A[0][0]);
    print(A[0][11]);
    print(BA[1][0][1]);
    print(A[0][0] * A[0][0]);

    Matrix I;
    for(int i = 0;i < L;i++){
        I[i][i] = get_diag(1);
    }

    Matrix D{};
    D[0][0] = A[0][0];

    int q;
    cin>>q;
    while(q--){
        int n,k,x;
        cin>>n>>k>>x;

        if(n == 1){
            cout<<0<<endl;
            return;
        }

        n--;

        Matrix RES = I;
        for(int i = 0;i < 30;i++){
            if(n >> i & 1){
                RES = RES * BA[i];
            }
        }

        Matrix ANS = D * RES;
        cout<<ANS[0][0][k][x]<<endl;
        //D * RES ->

    }
    


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