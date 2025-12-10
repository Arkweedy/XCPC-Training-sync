#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<size_t n>
using mat01 = array<array<int,n>,n>;

template<size_t n>
mat01<n> operator* (const mat01<n>&lhs, const mat01<n>&rhs)
{
    mat01<n> res{};
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            for(int k = 0;k < n;k++){
                res[i][j] |= lhs[i][k] & rhs[k][j];
            }
        }
    }
    return res;
}

void solve()
{
    constexpr int i = 4;
    //for(int i = 2;i <= 6;i++){
    cout<<"cnt when n = "<<i<<endl;
    ull up = 1ull << (i * i);
    ull mask = 0;
    //ull full = (1ull<<(i * i + 1)) - 1;
    mat01<i>full;
    for(auto& arr : full){
        arr.fill(1);
    }
    ull cnt = 0;
    for(int j = 0;j < i;j++){
        mask |= (1ull)<<(j * i + j);
    }
    for(ull j = 0;j <= up;j++){
        if((j & mask) != mask){
            continue;
        }
        mat01<i> a{};
        for(int k = 0;k < i * i;k++){
            int x = k / i, y = k % i;
            if(j >> k & 1){
                a[x][y] = 1;
            }
        }
        
        while(a * a != a){
            a = a * a;
        }
        if(a == full){
            cnt++;
        }
    }
    cout<<cnt<<endl;
    //}
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
    #ifdef LOCAL_DEBUG
        system("pause");
    #endif
    return 0;
}