#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ld = long double;
using namespace std;

//Create time: 2026.09.10 18:00:07

void solve()
{
    int n;
    i64 k;
    cin >> n >> k;
    vector<i64>a(n + 1);
    set<ll> s;
    map<ll,int> ma;
    ll cur = 0;
    s.insert(0);
    
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        if(i % 2 == 1)cur += a[i];
        else cur -= a[i];
        cur = (cur % k + k)%k;
        s.insert(cur);
    }
    int cnt = 0;
    for(ll num : s){
        //cerr << num << endl;
        ma[num] = ++cnt;
        ++cnt;
    }
    
    vector<i64>t(cnt + 2);

    cur = 0;
    t[1]++;
    t[2]--;
    for(int i = 1;i <= n;i++)
    {
        t[1] += a[i] / k;
        ll be = ma[cur];
        //cerr << cur << " ";
        if(i % 2 == 1)cur += a[i];
        else cur -= a[i];
        cur = (cur % k + k)%k;
        ll en = ma[cur];
        //cerr << cur << endl;

        if(en == be) continue;

        if(i % 2 == 1){
            be++;
            if(en > be){
                t[be]++;
                t[en + 1]--;
            }
            else{
                t[be]++;
                t[1]++;
                t[en+1]--;
            }
        }   

        else{
            be--;
            if(be == 0){
                be = cnt;
            }
            
            if(en > be){
                t[1]++;
                t[be+1]--;
                t[en]++;
            }
            else{
                t[en]++;
                t[be+1]--;
            }
        }
    }
    ll maxone = 0;
    ll minone = LLONG_MAX;
    ll cnts = 0;
    for(int i = 1;i <= cnt;i++){
        cnts += t[i];
        //cerr << cnts << endl;
        maxone = max(cnts,maxone);
        minone = min(cnts,minone);
    }
    cout << minone << ' ' << maxone << '\n';
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