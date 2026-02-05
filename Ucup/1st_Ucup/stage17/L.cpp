#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.31 18:16:52
constexpr int N = 1e6 + 1000;
vector<int>prime;
bitset<N + 1>isprime;
void seive()
{
    isprime.set();
    for(int i = 2;i <= N;i++){
        if(isprime[i]){
            prime.push_back(i);
        }
        for(auto p : prime){
            if(i * p > N)break;
            isprime[i * p].flip();
            if(i % p == 0)break;
        }
    }
    return;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    //constexpr int X = 1e6;
    // mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    // n = g() % X + 1;
    // k = g() % n + 1;
    // //n = 2; k = 0;
    //n = 707649 , k = 1089;
    

    if(n % 2 != k % 2){
        cout << -1 << "\n";
        return;
    }
    int m = (n - k) / 2;
    vector<int>f(n + 1, 1);
    int cnt = 0;
    auto add = [&](int p)->void
    {
        for(int i = 1;i * p <= n;i++){
            int x = i * p;
            int c = 0;
            while(x % p == 0){
                x /= p;
                c++;
            }
            if(c % 2 == 1){
                f[i * p] = -f[i * p];
                if(f[i * p] == -1)cnt++;
                else cnt--;
            }
        }
    };

    int sq = sqrt(n);
    while(sq * sq < n)sq++;

    for(auto p : prime){
        if(p > n || cnt == m)break;
        int ocnt = cnt;
        add(p);
        if(cnt > m || ocnt > cnt)add(p);
    }
    assert(cnt == m);

    for(int i = 1;i <= n;i++){
        cout << f[i] << " ";
    }
    cout << endl;
    return;

}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    seive();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}