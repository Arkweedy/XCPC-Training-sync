#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

vector<int> operator& (const vector<int>&lhs, const vector<int>& rhs)
{
    vector<int>res(lhs.size());
    for(int i = 0;i < lhs.size();i++){
        res[i] = lhs[i] & rhs[i];
    }
    return res;
}


void solve()
{
    int n, m;
    cin>>n>>m;
    vector<string>s(n);
    for(int i = 0;i < n;i++){
        cin>>s[i];
    }

    if(n > m){
        vector<string>ns(m,string(n,' '));
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                ns[j][i] = s[i][j];
            }
        }
        s = move(ns);
        swap(n, m);
    }

    vector<vector<int>>a(n,vector<int>(m));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            a[i][j] = s[i][j] - '0';
        }
    }

    //cerr<<__lg(0)<<" "<<__lg(1)<<" "<<__lg(2)<<" "<<__lg(3)<<endl;

    //sprase table
    int slen = __lg(n) + 1;
    vector<vector<vector<int>>>st(slen, vector<vector<int>>(n, vector<int>(m)));

    for(int i = 0;i < n;i++){
        st[0][i] = a[i];
    }

    for(int k = 1;k < slen;k++){
        for(int i = 0;i + (1 << k) -1 < n;i++){
            st[k][i] = st[k - 1][i] & st[k - 1][i + (1 << (k - 1))];
        }
    }

    auto query = [&](int l ,int r)->vector<int>
    {
        int k = __lg(r - l + 1);
        //cerr<<l<<" "<<r<<" "<<k<<" "<<r - (1 << k) + 1<<endl;
        return st[k][l] & st[k][r - (1 << k) + 1];
    };

    

    auto get1 = [&](int l, int r, int len)->int
    {
        int t = 0;
        l++,r++;
        int d = (r - 1) / (r - l + 1);
        if(r - l + 1 == len)return 0;
        for(int i = 0;i < 30;i++){
            if(d >> i & 1){
                l = max(l * 2 - r - 1, 1);
            }
            else{
                r = min(r * 2 - l + 1, len);
            }
            if(r - l + 1 == len){
                t = i + 1;
                break;
            }
            if(i == 29)t = 100;
        }
        //cerr<<t<<endl;
        return t;
    };

    auto get2 = [&](int l, int r, int len)->int
    {
        int t = 0;
        l++,r++;
        int d = (len - l) / (r - l + 1);
        if(r - l + 1 == len)return 0;
        for(int i = 0;i < 30;i++){
            if(d >> i & 1){
                r = min(r * 2 - l + 1, len);
            }
            else{
                l = max(l * 2 - r - 1, 1);
            }
            if(r - l + 1 == len){
                t = i + 1;
                break;
            }
            if(i == 29)t = 100;
        }
        //cerr<<t<<endl;
        return t;
    };

    auto get = [&](int l, int r, int len)->int
    {
        //cerr<<l<<" "<<r<<" "<<len<<endl;
        //cerr<<min(get1(l,r,len),get2(l,r,len))<<endl;
        return min(get1(l,r,len),get2(l,r,len));
    };

    int ans = 114514;
    for(int i = 0;i < n;i++){
        int k = 1e9;
        for(int j = i;j < n;j++){
            int nk = get(i, j, n);
            if(nk < k){
                auto v = query(i, j);
                // for(int y = 0;y < m;y++){
                //     cerr<<v[y]<<" ";
                // }
                // cerr<<endl;
                int len = 0;
                for(int x = 0;x < m;x++){
                    if(v[x] == 0)len = 0;
                    else len++;

                    if(len){
                        ans = min(ans, nk + get(x - len + 1, x, m));
                    }
                }
            }
            k = nk;
        }
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