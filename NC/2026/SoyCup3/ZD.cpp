#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.24 10:29:50

// mod 2^16
// even : * 2^15 -> 0, has 0 element?
// odd : * inv(a) -> 1

constexpr int M = 1 << 16;

template<typename T>
T exgcd(T a, T b, T &x, T &y)
{
    x = 1, y = 0;
    array<T, 4>m = {1, 0, 0 ,1};//matrix
    while(b != 0){
        T c = a / b;
        m = {m[1], m[0] - c * m[1], m[3], m[2] - c * m[3]};
        T t = a % b;
        a = b;
        b = t;
    }
    x = m[0], y = m[2];
    return a;
}

int inv(int a)
{
    int x, y;
    exgcd(a, M, x, y);
    x = (x % M + M) % M;
    return x;
}

// 256 0  = [8, 0] * [8]
// 0   0             [0] 

vector<int> operator+(vector<int>&a, vector<int>b)
{
    int n = a.size();
    vector<int>res(n);
    for(int i = 0;i < n;i++){
        res[i] = a[i] + b[i];
        if(res[i] >= M)res[i] -= M;
    }
    return res;
}

vector<int> operator*(vector<int>&a, int k)
{
    int n = a.size();
    k = (k % M + M) % M;
    vector<int>res(n);
    for(int i = 0;i < n;i++){
        res[i] = a[i] * k % M;
    }
    return res;
}

int lowbit(int x)
{
    return x & -x;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>a(n, vector<int>(m));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin >> a[i][j];
        }
    }
    // O(n^2 m)
    if(n > m){
        vector<vector<int>>b(m, vector<int>(n));
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                b[j][i] = a[i][j];
            }
        }
        swap(n, m);
        a = move(b);
    }

    auto swapcol = [&](int i, int j)->void
    {
        for(int k = 0;k < n;k++){
            swap(a[k][i], a[k][j]);
        }
    };

    //calc rank ?
    int p = 0;
    for(int i = 0;i < n;i++){
        //find a arg_j min_k a_ji = 2^k * x
        //reduce
        int t = p - 1;
        int mink = 1 << 16; 
        int none = 1;
        for(int j = p;j < n;j++){
            if(a[j][i] == 0)continue;
            none = 0;
            if(lowbit(a[j][i]) < mink){
                t = j;
                mink = lowbit(a[j][i]);
            }
        }
        if(none)continue;
        swap(a[p], a[t]);
        int k = __lg(mink);
        int inva = inv(a[p][i] >> k);
        for(int j = p + 1;j < n;j++){
            if(a[j][i] != 0){
                int coef = -inva * (a[j][i] >> k);
                a[j] = a[j] + a[p] * coef;
            }
        }
        p++;
    }

    // for(int i = 0;i < n;i++){
    //     for(int j = 0;j < m;j++){
    //         cerr << a[i][j] << " ";
    //     }
    //     cerr << endl;
    // }
    // cerr << endl;

    int ans = p;
    cout << ans << endl;
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