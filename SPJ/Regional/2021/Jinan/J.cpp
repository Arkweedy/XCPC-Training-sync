#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int power(int a, int p, int P)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}  

int inv(int a, int P)
{
    return power(a, P - 2, P);
}

int det(vector<vector<int>>a, int P)
{
    int n = a.size() - 1;
    int r = 1, fh = 0, l, j;
    for(int i = 1;i <= n;i++){
        for(j = i;j <= n;j++)if(a[j][i])break;
        if(j > n)return 0;
        if(i != j) swap(a[j],a[j]), fh^=1;
        r = 1ll * r * a[i][i] % P;
        int x = inv(a[i][i], P);
        for(int j = i;j <= n;j++){
            a[i][j] = 1ll * a[i][j] * x % P;
        }
        for(int j = i + 1;j <= n;j++){
            a[j][i] = P - a[j][i];
            for(int k = i + 1;k <= n;k++){
                a[j][k] = (a[j][k] + 1ll * a[j][i] * a[i][k]) % P;
            }
            a[j][i] = 0;
        }
    }
    if(fh)return (P - r) % P;
    return r;
}

int smod(string& s, int P)
{
    int res = 0;
    for(int i = 0;i < s.length();i++){
        res = 1ll * res * 10 % P;
        res += s[i] - '0';
    }
    return res % P;
}

// int check(int x)
// {
//     for(int i = 2;i * i <= x;i++){
//         if(x % i == 0)return false;
//     }
//     return true;
// }



void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;

    vector<vector<int>>a(n + 1,vector<int>(n + 1));
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cin>>a[i][j];
        }
    }

    vector<int>primes{998244353,683964889,777624703,298071289,851028547,295666291,174994691,243266251,490830761,755782121};

    auto check = [&](int P)->int
    {
        int moddet = det(a, P);
        int modstr = smod(s, P);
        //cerr<<moddet<<" "<<modstr<<endl;
        if(moddet == 0 && modstr == 0){
            return 0;
        }
        else if(moddet == modstr){
            return 1;
        }
        else if(moddet + modstr == P){
            return -1;
        }
        else{
            assert("error");
        }
        return 0;
    };

    for(auto P : primes){
        int res = check(P);
        //cerr<<res<<endl;
        if(res == 1){
            cout<<"+"<<endl;
            return;
        }
        else if(res == -1){
            cout<<"-"<<endl;
            return;
        }
        else{
            //cerr<<"can not check"<<endl;
        }
    }

    return;
    //mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    //constexpr int N = 1e9;
    // auto random_P = [&]()->int
    // {
    //     int p = g() % N;
    //     while(!check(p))p++;
    //     return p;
    // };

    // cout<<random_P()<<endl;
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