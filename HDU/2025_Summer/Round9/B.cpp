#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128;

using namespace std;


//template<>
//int MInt<0>::Mod = 998244353;
//int MInt<0>::Mod = 1000000007;
//constexpr int P = 998244353;
constexpr int P = 1000000007;
constexpr int PhiP = P - 1;
constexpr ll PP = 1ll * P * PhiP;


i128 Mpower(i128 a, i128 p)
{
    i128 res = 1;
    for (; p; p /= 2, a = a * a % PP) {
        if (p % 2) {
            res = res * a % PP;
        }
    }
    return res;
}

struct Info{
    i128 ans;
    i128 sum;//replace_left_to_plus_value
    i128 pmp;//pre_mul_plus_value
    i128 pm;//pre_mul_value
    i128 sm;//suf_mul_value
    bool all_mul;
    bool exist_left;

    Info(i128 x)
        :ans(x),
        sum(x),
        pmp(x),
        pm(x),
        sm(x),
        all_mul(1),
        exist_left(0){}

    Info() = default;
};

Info operator* (const Info& lhs, const Info& rhs)
{
    Info res{};
    res.all_mul = lhs.all_mul & rhs.all_mul;
    res.exist_left = lhs.exist_left | rhs.exist_left;
    if(rhs.all_mul)res.sm = lhs.sm * rhs.sm % PP;
    else res.sm = rhs.sm;
    if(lhs.all_mul)res.pm = lhs.pm * rhs.pm % PP;
    else res.pm = lhs.pm;
    res.sum = (lhs.sum + rhs.sum - lhs.sm - rhs.pm + lhs.sm * rhs.pm) % PP;
    if(lhs.exist_left)res.pmp = lhs.pmp;
    else res.pmp = (lhs.pmp + rhs.pmp - lhs.sm - rhs.pm + lhs.sm * rhs.pm) % PP;
    if(res.exist_left)res.ans = res.pmp * Mpower(2,(res.sum - res.pmp + PP) % PP) % PP;
    else res.ans = res.sum;
    return res;
}

Info operator+ (const Info& lhs, const Info& rhs)
{
    Info res{};
    res.all_mul = 0;
    res.exist_left = lhs.exist_left | rhs.exist_left;
    res.sm = rhs.sm;
    res.pm = lhs.pm;
    if(lhs.exist_left)res.pmp = lhs.pmp;
    else res.pmp = (lhs.pmp + rhs.pmp) % PP;
    res.sum = (lhs.sum + rhs.sum) % PP;
    if(res.exist_left)res.ans = res.pmp * Mpower(2,(res.sum - res.pmp + PP) % PP) % PP;
    else res.ans = res.sum;
    return res;
}

Info operator<< (const Info& lhs, const Info& rhs)
{
    Info res{};
    res.all_mul = 0;
    res.exist_left = 1;
    res.sm = rhs.sm;
    res.pm = lhs.pm;
    res.pmp = lhs.pmp;
    res.sum = (lhs.sum + rhs.sum) % PP;
    res.ans = res.pmp * Mpower(2,(res.sum - res.pmp + PP) % PP) % PP;
    return res;
}

void solve()
{
    int n;
    cin>>n;
    vector<Info>a(n + 1);
    vector<vector<int>>g(n + 1);
    vector<int>indeg(n + 1);
    vector<int>ope(n + 1);
    vector<pair<int,int>>opcnt(n + 1);
    for(int i = 1;i <= n;i++){
        char op;
        cin>>op;
        if(op == 'N'){
            ope[i] = 1;
            ll x;
            cin>>x;
            a[i] = Info(x);
        }
        else if(op == '<'){
            ope[i] = 2;
            int x, y;
            cin>>x>>y;
            g[x].push_back(i);
            g[y].push_back(i);
            opcnt[i] = {x,y};
            indeg[i] = 2;
            //a[i] = a[x] * power(i128(2), a[y]) % PP;
        }
        else if(op == '+'){
            ope[i] = 3;
            int x, y;
            cin>>x>>y;
            g[x].push_back(i);
            g[y].push_back(i);
            opcnt[i] = {x,y};
            indeg[i] = 2;
        }
        else if(op == '*'){
            ope[i] = 4;
            int x, y;
            cin>>x>>y;
            g[x].push_back(i);
            g[y].push_back(i);
            opcnt[i] = {x,y};
            indeg[i] = 2;
        }
    }

    queue<int>q;
    for(int i = 1;i <= n;i++){
        if(ope[i] == 1){
            q.push(i);
        }
    }
    
    while(!q.empty()){
        int p = q.front();
        q.pop();
        auto [x, y] = opcnt[p];
        //cerr<<"calc "<<p <<" , op = "<<ope[p]<<endl;
        if(ope[p] == 2){// <<
            a[p] = a[x] << a[y];
        }
        else if(ope[p] == 3){// +
            a[p] = a[x] + a[y];
        }
        else if(ope[p] == 4){// *
            a[p] = a[x] * a[y];
        }

        for(auto s : g[p]){
            indeg[s]--;
            if(indeg[s] == 0){
                q.push(s);
            }
        }
    }

    for(int i = 1;i <= n;i++){
        ll x = a[i].ans % P;
        cout<<x<<"\n";
    }
    cout<<endl;
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