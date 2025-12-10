#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 200001;
vector<int>prime;
bitset<N + 1>isprime;
vector<int>mu;

void seive()
{
    isprime.set();
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) 
            prime.push_back(i);
        
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)break;
            isprime.flip(i * p);
            if (i % p == 0)break;
        }
    }
}

void solve()
{
    int n;
    cin>>n;
    int m = n;
    vector<int>ans;
    for(auto p : prime){
        while(n % p == 0){
            n /= p;
            ans.push_back(p);
        }
        if(n == 1)break;
    }
    cout<<m<<"="<<ans[0];
    for(int i = 1;i <ans.size();i++){
        cout<<"*"<<ans[i];
    }
    cout<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    seive();
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}