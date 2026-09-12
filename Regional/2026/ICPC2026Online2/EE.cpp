#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;
using namespace std;

constexpr int N = 1e7;

vector<int>prime;
bitset<N + 1>isprime;
vector<int>phi;

void seive()
{
    isprime.set();
    phi.resize(N + 1);
    phi[1] = 0;
    for(int i = 2;i <= N;i++){
        if(isprime[i]){
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for(auto p : prime){
            if(i * p > N)break;
            isprime[i * p].flip();
            if(i % p == 0){
                phi[i * p] = phi[i] * p;
                break;
            }
            else{
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }
    return;
}



int ord(int x, int n)
{
    int res = 1;
    int a = x;
    int pn = phi[n];
    
    if(gcd(x, n) != 1)return 0;
    while(a != 0 && a != 1){
        a = 1ll * a * x % n;
        res++;
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    int res = 0;
    vector<int>cnt(n + 1);
    int sum = 0;
    // for(int i = 1;i <= n;i++){
    //     cnt[ord(i, n)]++;
    // }
    // for(int i = 0;i <= n;i++){
    //     sum += i * cnt[i];
    // }
    // cout << "######" << endl;
    // cout << sum << endl;
    // for(int i = 0;i <= n;i++){
    //     cout << cnt[i] << " ";
    // }
    // cout << endl;
    // for(int i = 0;i <= n;i++){
    //     cerr << i << " " << cnt[i] << endl;
    // }


    cout<<"LLLLL"<<endl;
    int g=phi[n];
    i64 ans=0;
    for(int x=1;x<=g;x++)
        if(g%x==0){
            ans+=1ll * x*phi[x];
        }
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    seive();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}



