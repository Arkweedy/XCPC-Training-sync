#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

vector<int>digit;
vector<vector<int>>xx;
vector<vector<int>>popc;
int vs[1<<21], f[1<<21];
int len;

void init()
{
    xx.resize(10);
    digit.resize(10);
    popc.resize(21 + 1);
    xx[0] = {1,1,1,1,1,1,0};
    xx[1] = {0,1,1,0,0,0,0};
    xx[2] = {1,1,0,1,1,0,1};
    xx[3] = {1,1,1,1,0,0,1};
    xx[4] = {0,1,1,0,0,1,1};
    xx[5] = {1,0,1,1,0,1,1};
    xx[6] = {1,0,1,1,1,1,1};
    xx[7] = {1,1,1,0,0,0,0};
    xx[8] = {1,1,1,1,1,1,1};
    xx[9] = {1,1,1,1,0,1,1};
    for(int i = 0;i <= 9;i++){
        for(int j = 0;j < 7;j++){
            if(xx[i][j]){
                digit[i] |= 1 << j;
            }
        }
    }
    len = 1 << 21;
    for(int i = 0;i < len;i++){
        popc[__popcount(i)].push_back(i);
    }
}

void solve()
{
    int n,m;
    cin>>n>>m;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<int>val(n);
    set<int>st;
    for(int i = 0;i < m;i++){
        int x = 1;
        for(int j = 0;j < i;j++){
            x *= 10;
        }
        for(int j = 0;j < n;j++){
            int y = a[j] / x % 10;
            val[j] |= digit[y] << (i * 7);
        }
    }
    int leq = 0;
    vector<int>occnt(21);
    for(int i = 0;i < n;i++){
        st.insert(val[i]);
        for(int j = 0;j < 21;j++){
            if(val[i] >> j & 1)occnt[j]++;
        }
    }
    for(int i = 0;i < 21;i++){
        if(occnt[i] == 0)leq |= 1 << i;
    }
    int lst = __lg(st.size());

    if(n <= 21){
        //divide all val need at least ?
        for(int i = lst;i <= 21;i++){
            for(auto msk : popc[i]){
                if(msk & leq){
                    continue;
                }
                int cnt = 0;
                for(int j = 0;j < n;j++){
                    vs[val[j]&msk]++;
                    if(vs[val[j] & msk] == 1)cnt++;
                }
                for(int j = 0;j < n;j++){
                    vs[val[j]&msk] = 0;
                }
                if(cnt == n){
                    cout<<i<<endl;
                    return;
                }
            }
        }
    }
    else{
        // 超集和
        for (int j = 0; j < (1 << 21); j++) f[j] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int mask = val[i] ^ val[j];
                mask = (len - 1) ^ mask;
                f[mask] = 1;
            }
        }
        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < len; j++) {
                if (!(j >> i & 1)) f[j] |= f[j ^ (1 << i)];
            }
        }
        for (int i = lst; i <= 21; i++) {
            for (auto msk : popc[i]) {
                if (!f[msk]) {
                    cout << i << '\n';
                    return;
                }
            }
        }
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    init();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}