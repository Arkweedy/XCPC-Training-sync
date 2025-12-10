#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 51123987;

vector<int> manacher(string s)
{
    string t = "#";
    for(auto ch : s){
        t += ch;
        t += '#';
    }

    int n = t.size();
    vector<int>r(n);
    int len = -1;
    for(int i = 0, j = 0;i < n;i++){
        if (2 * j - i >= 0 && j + r[j] > i) {//in radius
            r[i] = min(r[2 * j - i], j + r[j] - i);
        }
        while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]]) {
            r[i] += 1;
        }
        if (i + r[i] > j + r[j]) {
            j = i;
        }
    }
    return r;
}

void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    auto r = manacher(s);
    vector<int>lcnt(n + 1),rcnt(n + 1);
    for(int i = 0;i < n * 2 + 1;i++){
        //diff
        r[i] /= 2;
        if(i % 2 == 0){//even
            // i / 2 -> s[r]
            // i / 2 - r[i] ~ i / 2 + r[i] - 1
            lcnt[i / 2 - r[i]]++;
            lcnt[i / 2]--;
            rcnt[i / 2]++;
            rcnt[i / 2 + r[i]]--;
            //cerr<<"ok"<<endl;
        }
        else{
            // i / 2 -> s[mid]
            // i / 2 - r[i] + 1 ~ i / 2 + r[i] - 1
            lcnt[i / 2 - r[i] + 1]++;
            lcnt[i / 2 + 1]--;
            rcnt[i / 2]++;
            rcnt[i / 2 + r[i]]--;
        }
    }
    
    ll sum = lcnt[0];
    for(int i = 1;i < n;i++){
        lcnt[i] += lcnt[i - 1];
        rcnt[i] += rcnt[i - 1];
        lcnt[i] %= P;
        rcnt[i] %= P;
        sum += lcnt[i];
        sum %= P;
    }
    ll ans = sum * (sum - 1) / 2;
    for(int i = 1;i < n;i++){
        rcnt[i] += rcnt[i - 1];
        rcnt[i] %= P;
        ans = (ans - (1ll * rcnt[i - 1] * lcnt[i] % P) + P) % P;
    }
    cout<<ans<<endl;
    return;

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
    return 0;
}