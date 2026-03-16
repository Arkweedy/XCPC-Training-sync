#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.03.14 22:45

void solve()
{
    int n, k, p, m;
    cin >> n >> k >> p >> m;
    p--;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    queue<int>q;
    for(int i = k;i < n;i++){
        q.push(i);
    }
    set<pair<int,int>>s;
    for(int i = 0;i < k;i++){
        s.insert({a[i], i});
    }
    int ans = 0;
    while(1){
        if(s.count({a[p], p})){
            if(m >= a[p]){
                ans++;
                m -= a[p];
                s.extract({a[p], p});
                q.push(p);
            }
            else{
                break;
            }
        }
        else{
            auto [x, id] = *s.begin();
            if(m >= x){
                m -= x;
                s.extract({x, id});
                q.push(id);
            }
            else{
                break;
            }
        }
        int x = q.front();
        q.pop();
        s.insert({a[x], x});
    }
    cout << ans << endl;
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