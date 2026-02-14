#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.14 20:38

constexpr int N = 10000001;
vector<int>prime;
bitset<N + 1>isprime;
vector<int>lpf;
vector<int>pid;

// p -> id, 
vector<int>ma, mac, uni, sec;

void seive()
{
    isprime.set();
    lpf.resize(N);
    pid.resize(N);
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            prime.push_back(i);
            lpf[i] = i;
            pid[i] = prime.size() - 1;
        }
        
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)break;
            isprime.flip(i * p);
            lpf[i * p] = p;
            if (i % p == 0)break;
        }
    }
    int c = prime.size();
    ma.resize(c);
    mac.resize(c);
    sec.resize(c);
    uni.resize(c, 1);
}

constexpr int P = 998244353;

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



void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    vector<int>upt;
    for(int i = 0;i < n;i++){
        int x = a[i];
        int lastp = 0;
        int lastc = 0;
        int lpid = -1;
        while(x != 1){
            if(lpf[x] != lastp){
                //calc lastp;
                if(lpid != -1){
                    if(lastc > mac[lpid]){
                        ma[lpid] = i;
                        sec[lpid] = mac[lpid];
                        mac[lpid] = lastc;
                        uni[lpid] = 1;  
                    }
                    else if(lastc == mac[lpid]){
                        sec[lpid] = mac[lpid];
                        uni[lpid] = 0;
                    }
                    else if(lastc > sec[lpid]){
                        sec[lpid] = lastc;
                    }
                }
                lastp = lpf[x];
                lastc = 0;
                lpid = pid[lpf[x]];
                upt.push_back(lpid);
            }
            lastc++;
            x = x / lpf[x];
        }
        if(lpid != -1){
            if(lastc > mac[lpid]){
                ma[lpid] = i;
                sec[lpid] = mac[lpid];
                mac[lpid] = lastc;
                uni[lpid] = 1;
            }
            else if(lastc == mac[lpid]){
                sec[lpid] = mac[lpid];
                uni[lpid] = 0;
            }
            else if(lastc > sec[lpid]){
                sec[lpid] = lastc;
            }
        }
    }
    
    sort(upt.begin(),upt.end());
    upt.erase(unique(upt.begin(),upt.end()), upt.end());

    int ans = 1;
    for(auto id : upt){
        ans = 1ll * ans * power(prime[id], mac[id]) % P;
    }
    

    vector<int>res(n, ans);
    for(auto id : upt){
        if(uni[id]){
            res[ma[id]] = 1ll * res[ma[id]] * power(power(prime[id], P - 2), mac[id] - sec[id]) % P;
        }
        uni[id] = 1;
        mac[id] = sec[id] = ma[id] = 0;
    }

    for(int i = 0;i < n;i++){
        cout << res[i] << " ";
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