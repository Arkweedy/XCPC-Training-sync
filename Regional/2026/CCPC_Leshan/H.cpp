#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;


auto get(i64 n, i64 m)->vector<pair<int,int>>
{
    vector<pair<int,int>>ans;
    int q = 0;
    i64 sum = 0;
    for(int i = n;i >= 1;i--){
        vector<pair<int, int>>buf;
        for(int j = 0;j + i - 1 < n;j++){
            buf.push_back({j, j + i - 1});
            sum += i;
            q++;
            if(q == n){
                for(int i = (int)buf.size() - 1;i >= 0;i--){
                    ans.push_back(buf[i]);
                }
                goto out;
            }
        }
        for(int i = (int)buf.size() - 1;i >= 0;i--){
            ans.push_back(buf[i]);
        }
    }
    out:

    reverse(ans.begin(),ans.end());

    i64 over = sum - m;

    if(over < 0)return vector<pair<int,int>>{};
    
    for(int i = 0;i < n;i++){
        auto [l, r] = ans[i];
        //assert(l <= i && i <= r);
        int dlen = r - l + 1 - 1;
        if(over >= dlen){
            ans[i] = {i, i};
            over -= dlen;
        }
        else{
            int dlen1 = i - l;
            if(dlen1 > over){
                ans[i].first += over;
                break;
            }
            else{
                ans[i].first = i;
                over -= dlen1;
                ans[i].second -= over;
                break;
            }
        }
    }

    assert(ans.size() == n);
    i64 ck = 0;
    for(auto [l, r] : ans){
        ck += r - l + 1;
    }
    assert(ck == m);

    return ans;
}



void solve1()
{
    i64 n, m;
    cin >> n >> m;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    auto ans = get(n, m);

    for(auto [l, r] : ans){
        cout << l + 1 << " " << r + 1 << endl;
    }
    return;
}

void solve2()
{
    i64 n, x;
    cin >> n >> x;
    vector<i64>a(n);
    i64 sum = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i];
    }
    vector<i64>p(n);
    for(int i = 0;i < n;i++){
        p[i] = a[i];
        if(i > 0)p[i] += p[i - 1];
    }

    auto calc = [&](pair<int,int>pr)->i64
    {
        auto [l, r] = pr;
        i64 res = p[r];
        if(l > 0)res -= p[l - 1];
        return res;
    };

    auto check = [&](i64 m)->bool
    {
        auto vec = get(n, m);
        if(vec.empty())return false;
        i64 sum = 0;
        for(auto pr : vec){
            sum += calc(pr);
        }
        return (sum <= x);
    };


    i64 L = n, R = 5e10;
    while(R - L > 1){
        i64 M = L + R >> 1;
        if(check(M)){
            L = M;
        }
        else{
            R = M;
        }
    }
    cout << L << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int tt = 1;
    cin >> tt;
    if(s == "cat"){
        while(tt--){
            solve1();
        }
    }
    else{
        while(tt--){
            solve2();
        }
    }
    return 0;
}