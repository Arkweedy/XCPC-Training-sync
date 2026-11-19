#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C2.cpp Create time : 2026.11.06 23:09

constexpr int N = 200000;
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
    int a, b;
    cin >> a >> b;
    //cerr << a << " " << b << endl;
    if(a == b){
        cout << 0 << endl;
        return;
    }

    if(gcd(b - a, a) == 1){
        cout << 1 << endl;
        cout << b - a << endl;
        return;
    }

    auto get = [&](int x)->int
    {
        if(x == 1)return x;
        if(isprime[x])return x;
        int p = lower_bound(prime.begin(),prime.end(), x) - prime.begin();
        //while(gcd(prime[p] - x, x) != 1)p++;
        return prime[p];
    };

    int x = get(a);
    //cerr << x << endl;
    if(x < b){
        while(b % x == 0)x = get(x + 1);
        cout << 2 << endl;
        cout << x - a << " " << b - x << endl;
        return;
    }

    // dis ~ log
    // bfs
    map<int, int>dis,pre;
    queue<int>q;
    q.push(a);
    dis[a] = 0;
    while(1){
        int x = q.front();
        q.pop();
        for(int i = 1;i + x <= b;i++){
            if(gcd(i, x) != 1)continue;
            if(!dis.count(x + i)){
                dis[x + i] = dis[x] + 1;
                pre[x + i] = x;
                q.push(x + i);
                if(x + i == b)goto out;
                
            }
        }
    }
    out:
    int p = b;
    vector<int>ans;
    while(p != a){
        ans.push_back(p - pre[p]);
        p = pre[p];
    }
    reverse(ans.begin(),ans.end());
    cout << ans.size() << endl;
    for(int i = 0;i < ans.size();i++){
        cout << ans[i] << " ";
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