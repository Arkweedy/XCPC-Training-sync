#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int pr[] = {683964889,777624703,298071289,851028547,295666291,174994691,243266251,490830761,755782121};

int power(int a, int p, int i)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % pr[i];
        a = 1ll * a * a % pr[i];
        p >>= 1;
    }
    return res;
}  

int inv(int a, int i)
{
    return power(a, pr[i] - 2, i);
}

const int N = 110;

int a[N][N];
int n;
int det(int t)
{
    int r = 1, fh = 0, l, j;
    for(int i = 1;i <= n;i++){
        for(j = i;j <= n;j++)if(a[j][i])break;
        if(j > n)return 0;
        if(i != j) swap(a[j],a[i]), fh^=1;
        r = 1ll * r * a[i][i] % pr[t];
        int x = inv(a[i][i], t);
        for(int j = i;j <= n;j++){
            a[i][j] = 1ll * a[i][j] * x % pr[t];
        }
        for(int j = i + 1;j <= n;j++){
            a[j][i] = pr[t] - a[j][i];
            for(int k = i + 1;k <= n;k++){
                a[j][k] = (a[j][k] + 1ll * a[j][i] * a[i][k]) % pr[t];
            }
            a[j][i] = 0;
        }
    }
    if(fh)return (pr[t] - r) % pr[t];
    return r;
}

int smod(string& s, int t)
{
    int res = 0;
    for(int i = 0;i < s.size();i++){
        res = 1ll * res * 10 % pr[t];
        res += s[i] - '0';
    }
    return res % pr[t];
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

    cin>>n;
    string s;
    cin>>s;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cin>>a[i][j];
        }
    }

    

    auto check = [&](int i)->int
    {
        
        int modstr = smod(s, i);
        //cerr<<moddet<<" "<<modstr<<endl;
        if(modstr == 0)return 0;

        int moddet = det(i);
        if((moddet - modstr)%pr[i] == 0){
            return 1;
        }
        if((moddet + modstr)%pr[i] == 0){
            return -1;
        }
        assert(0);

        return 0;
    };

    for(int i=0;i<9;i++){

        int res = check(i);
        //cerr<<res<<endl;
        if(res == 1){
            cout<<"+"<<'\n';
            return;
        }
        else if(res == -1){
            cout<<"-"<<'\n';
            return;
        }
        else{
            //
        }
        //break;
    }
    cout<<"+"<<'\n';
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