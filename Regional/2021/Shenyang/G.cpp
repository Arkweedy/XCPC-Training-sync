#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
constexpr int P = 998244353;

int lowbit(int x)
{
    return x & -x;
}

struct state{
    vector<int>a;
    int last;

    bool operator<(state b)
    {
        if(a!=b.a)return a < b.a;
        return last>b.last;//???
    }

    bool operator==(state b)
    {
        //compare a
        return a == b.a && last == b.last;
    }

    state () {}
    state(vector<int>a, int last) {
        this->a = a;
        this->last = last;
    }
};

void solve()
{
    int n;
    string s;
    cin>>n>>s;
    int tot = 0;
    map<int,int>mp;
    for(auto& x : s){
        if(!mp.count(x))mp[x] = tot++;
        x = mp[x] + 'a';
    }
    int k = mp.size();
    vector<int>last(k);
    for(int i = 0;i < n;i++){
        last[s[i] - 'a'] = i;
    }
    //suf
    int len = 1 << k;
    vector<int>suf(len, n);
    for(int i = 1;i < len;i++){
        suf[i] = min(suf[i - lowbit(i)] , last[__lg(lowbit(i))]);
    }

    //presum
    vector<vector<int>>presum(n,vector<int>(k));
    presum[0][s[0] - 'a']++;
    for(int i = 1;i < n;i++){
        presum[i] = presum[i - 1];
        presum[i][s[i] - 'a']++;
    }

    vector<vector<int>>la(n,vector<int>(k));
    for(int i = 0;i < n;i++){
        if(i){
            la[i] = la[i - 1];
        }
        la[i][s[i] - 'a'] = i; 
    }

    auto get = [&](int l, int r, int ch)->int
    {
        //cerr<<l<<" "<<r<<" "<<ch<<endl;
        if(l > r)return 0;//
        return presum[r][ch] - (l > 0 ? presum[l - 1][ch] : 0);
    };

    //dp
    int all = len - 1;
    vector<state>dp(len,{vector<int>(), -1});
    for(int i = 1;i < len;i++){
        for(int j = 0;j < k;j++){
            if(i >> j & 1){
                if(dp[i ^ (1 << j)] == dp[0] && (i ^ (1 << j)) != 0)continue;
                auto [vec, last] = dp[i ^ (1 << j)];
                int cnt = get(last + 1, suf[all ^ i] - 1, j);
                //cerr<<"#"<<cnt<<endl;
                //if(i==3) return ;
                if(cnt == 0)continue;
                vec.push_back(cnt);
                int nlast = la[suf[all ^ i] - 1][j];
                dp[i] = dp[i] < state(vec,nlast) ? state(vec,nlast): dp[i];
            }
        }
    }
    // for(int i = 0;i < len;i++){
    //     auto [vec, last] = dp[i];
    //     for(auto x : vec){
    //         cerr<<x<<" ";
    //     }
    //     cerr<<last<<endl;
    // }
//    return;
    string ans;
    auto res = dp[all].a;
    for(int i = 0;i < k;i++){
        ans += string(res[i], 'a' + k - i - 1);
    }
    cout<<ans<<endl;
    return;

    

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
}