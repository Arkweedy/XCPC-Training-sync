#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.24 14:01:22

// n = \prod p_i^{k_i}, k_i > 0
// n = \sum_factors 
// if n != n / p_i
// -> 

// 0 1 2 3
// a a a a
// b c b c
// d e f d -> all ok

// lcm(1, 2, ... k) -> period
// period = p >= lcm(1, 2, ... k) -> ans >= k

// if use min period to check
// lcm(1, 2, ..., k) increase faster than k(k + 1) / 2
// actually we can solve gauss ?

// check with binary search
// for every checked k, find enough eq to check that error P is small enough
// how to generate eq ?
// eg ? when n is small ,
// n = 10, k = 4?
// 1 2 3 4 5 6 7 8 9 10
// a a a a a a a a a a
// b c b c b c b c b c
// d e f d e f d e f d
// g h i j g h i j g h 
// 1 + 6 = 9 + 10 (check mod 1,2,3,4?)
// use CRT ? 
// i try 3 eq, but only can make one

// how this problem std make?
// check rank ?  

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

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