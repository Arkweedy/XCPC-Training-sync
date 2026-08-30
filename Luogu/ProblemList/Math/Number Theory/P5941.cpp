#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.08.21 11:23:27
int P;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int powerF(int a, int b, int d, int p) //power(a + bw, p), w^2 = d, d/p = -1
{
    int ra = 1, rb = 0;
    while(p){
        if(p & 1){
            int nra = (1ll * a * ra + 1ll * b * rb % P * d) % P;
            int nrb = (1ll * a * rb + 1ll * b * ra) % P;
            ra = nra;
            rb = nrb;
        }
        int na = (1ll * a * a + 1ll * b * b % P * d) % P;
        int nb = 2ll * a * b % P;
        a = na;
        b = nb;
        p >>= 1;
    }
    return ra;
}

int Cipolla(int a)
{
    if(a == 0)return 0;
    int ea = power(a, (P - 1) / 2);
    if(ea == P - 1)return -1;
    int r, d, ed;
    mt19937 rng(random_device{}());
    do{
        r = rng() % P;
        d = (1ll * r * r - a + P) % P;
        ed = power(d, (P - 1) / 2);
    }while(ed == 1);
    int x = powerF(r, 1, d, (P + 1) / 2);
    return x;
}

void solve()
{
    int n;
    cin >> n >> P;
    if(n == 0){
        cout << 0 << endl;
        return;
    }
    int x = Cipolla(n);
    if(x == -1){
        cout << "Hola!" << endl;
        return;
    }
    int y = P - x;
    if(x > y)swap(x, y);
    cout << x << " " << y << endl;
    return;
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