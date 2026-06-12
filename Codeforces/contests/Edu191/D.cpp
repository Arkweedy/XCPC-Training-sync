#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.06.09 23:08

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    map<int,int>l,r,c;
    for(int i = 0;i < n;i++){
        if(l.count(a[i]) == 0)l[a[i]] = i;
        r[a[i]] = i;
        c[a[i]]++;
    }
    vector<int>p;
    for(auto [x, cnt] : c){
        if(r[x] - l[x] + 1 != cnt){
            p.push_back(x);
        }
    }

    if(p.size() == 0){
        cout << "YES" << endl;
        return;
    }
    if(p.size() >= 3){
        cout << "NO" << endl;
        return;
    }

    auto check = [&](int i, int j)->bool
    {
        if(i < 0 || i >= n)return false;
        if(j < 0 || j >= n)return false;
        map<int,int>f,g,h;
        swap(a[i], a[j]);
        for(int i = 0;i < n;i++){
            if(f.count(a[i]) == 0)f[a[i]] = i;
            g[a[i]] = i;
            h[a[i]]++;
        }
        swap(a[i], a[j]);
        for(auto [x, cnt] : h){
            if(g[x] - f[x] + 1 != cnt){
                return false;
            }
        }
        return true;
    };

    if(p.size() == 1 || p.size() == 2){
        int x = p[0];
        int L = l[x], R = r[x];
        int mi = R, ma = L;
        for(int i = L; i <= R;i++){
            if(a[i] != x){
                mi = min(mi, i);
                ma = max(ma, i);
            }
        }
        if(check(L, ma) || check(R, mi) || check(L, R + 1) || check(R, L - 1)){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
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