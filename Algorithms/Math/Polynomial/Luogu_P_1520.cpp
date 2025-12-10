#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 20001;
vector<int>prime;
bitset<N + 1>isprime;
vector<int>mu;

void seive()
{
    isprime.set();
    mu.resize(N + 1);
    isprime[0] = isprime[1] = 0;
    mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            prime.push_back(i);
            mu[i] = -1;
        }
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)
                break;
            isprime.flip(i * p);
            //mu
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            else {
                mu[i * p] = mu[i] * (-1);
            }
        }
    }
}
constexpr int M = 5001;
vector<vector<pair<int,int>>>cycpoly;

vector<pair<int,int>> mul(const vector<pair<int,int>>&lhs,const int &rhs, int expr)//rhs - 1
{
    map<int,int>poly;
    vector<pair<int,int>>polyv;
    if(expr == 0)return lhs;
    else if(expr == 1){
        for(const auto&[q,b]:lhs){
            poly[rhs + q] += b;
            poly[q] -= 1;
        }
        for(auto pr : poly){
            if(pr.second != 0){
                polyv.push_back(pr);
            }
        }
    }else{// 1 / rhs 
        int len = lhs.back().first - rhs;
        vector<int>k(len + 1);
        for(const auto&[q,b]:lhs){
            for(int i = 0;i + q <= len;i += rhs){
                k[i + q] -= b; 
            }
        }
        for(int i = 0;i <= len;i++){
            if(k[i] != 0){
                polyv.push_back({i,k[i]});
            }
        }
    }
    return polyv;
}

void init()
{
    cycpoly.resize(M + 1,vector<pair<int,int>>(1,{0,1}));
    for(int i = 1;i <= M;i++){
        for(int j = i;j <= M;j += i){
            if(mu[j / i] == 1)
            cycpoly[j] = mul(cycpoly[j],i,mu[j / i]);
        }
    }
    for(int i = 1;i <= M;i++){
        for(int j = i;j <= M;j += i){
            if(mu[j / i] == -1)
            cycpoly[j] = mul(cycpoly[j],i,mu[j / i]);
        }
    }
    return;
}

void solve()
{
    int n;
    cin>>n;
    vector<vector<pair<int,int>>>pfac;
    for(int i = 1;i <= n;i++){
        if(n % i == 0){
            pfac.push_back(cycpoly[i]);
        }
    }
    sort(pfac.begin(),pfac.end(),[&](const vector<pair<int,int>>&l,const vector<pair<int,int>>&r)->bool
    {
        int le = l.size() - 1,re = r.size() - 1;
        for(;le >=0 && re >= 0;le--,re--){
            if(l[le].first != r[re].first){
                return l[le].first < r[re].first;
            }else if(abs(l[le].second) != abs(r[re].second)){
                return abs(l[le].second) < abs(r[re].second);
            }else if(l[le].second != r[re].second){
                return l[le].second < r[re].second;
            }
        }
        return le < re;
    });
    auto print = [&](vector<pair<int,int>>&poly)->void
    {
        cout<<"(";
        for(int i = poly.size() - 1;i >=0 ;i--){
            if(poly[i].second < 0)cout<<"-";
            else if(i != poly.size() - 1)cout<<"+";
            if(abs(poly[i].second) != 1 || poly[i].first == 0)cout<<abs(poly[i].second);
            if(poly[i].first != 0 && poly[i].first != 1)cout<<"x^"<<poly[i].first;
            else if(poly[i].first == 1)cout<<"x";
        }
        cout<<")";
    };
    for(int i = 0;i < pfac.size();i++){
        print(pfac[i]);
    }
    cout<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    seive();
    init();
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}