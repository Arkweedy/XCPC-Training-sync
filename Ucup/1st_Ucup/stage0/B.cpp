#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.03.06 16:56

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>a(n + 2);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    string s;
    cin >> s;
    s = '1' + s + '1';

    vector<i64>f(n + 2), g(n + 2);
    deque<i64>que;
    que.push_back(0);
    for(int i = 1; i <= n + 1;i++){
        while(!que.empty() && que.front() + k < i)que.pop_front();
        f[i] = f[que.front()] + a[i];
        if(s[i] == '1')que.clear();
        while(!que.empty() && f[que.back()] >= f[i])que.pop_back();
        que.push_back(i);
    }
    que.clear();
    que.push_back(n + 1);
    for(int i = n; i >= 0;i--){
        while(!que.empty() && i + k < que.front())que.pop_front();
        g[i] = g[que.front()] + a[i];
        if(s[i] == '1')que.clear();
        while(!que.empty() && g[que.back()] >= g[i])que.pop_back();
        que.push_back(i);
    }

    // for(int i = 0;i <= n + 1;i++){
    //     cerr << f[i] << ' ';
    // }
    // cerr << endl;
    // for(int i = 0;i <= n + 1;i++){
    //     cerr << g[i] << ' ';
    // }
    // cerr << endl;

    int q;
    cin >> q;
    while(q--){
        int p, v;
        cin >> p >> v;
        swap(a[p], v);
        vector<i64>nf(k);
        que.clear();
        
        for(int i = max(0, p - k);i < p;i++){
            while(!que.empty() && que.front() + k < i)que.pop_front();
            if(s[i] == '1')que.clear();
            while(!que.empty() && f[que.back()] >= f[i])que.pop_back();
            que.push_back(i);
        }
        for(int i = p;i < min(p + k, n + 2);i++){
            while(que.front() + k < i)que.pop_front();
            nf[i - p] = (que.front() >= p ? nf[que.front() - p] : f[que.front()]) + a[i];
            if(s[i] == '1')que.clear();
            while(!que.empty() && (que.back() >= p ? nf[que.back() - p] : f[que.back()]) >= nf[i - p])que.pop_back();
            que.push_back(i);
        }
        i64 ans = 1e15;
        for(int i = p;i < min(p + k, n + 2);i++){
            ans = min(ans, nf[i - p] + (i == p ? g[i] - v : g[i] - a[i]));
        }
        cout << ans << endl;
        swap(a[p], v);
    }
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