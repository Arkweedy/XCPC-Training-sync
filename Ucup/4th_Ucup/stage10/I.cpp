#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.02 15:06:10

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

bool debug = 0;

void solve()
{
    int n;
    string s;
    n = 100000;
    s.resize(n);
    for(int i=0;i<n;i++)s[i]  = char('0' + rng() % 2);

    //cout<<s<<endl;
    if(!debug){
        cin>>n>>s;
    }
    vector<int>a,b;
    for(int i=0;i<n;){
        bool ok = 0;
        for(int len=1;len<=4;len++){
            if(i + 2 * len > n)break;
            if(s.substr(i,len) == s.substr(i+len,len)){
                ok = 1;
                for(int j=0;j<len;j++)a.push_back(i+j),b.push_back(i+len+j);
                i += 2 * len;
                break;
            }
        }
        if(!ok)i++;
    }
    assert(a.size() >= 42000);
    if(!debug){
        cout<<a.size()<<'\n';
        for(auto x:a)cout<<x<<' ';
        cout<<'\n';
        for(auto x:b)cout<<x<<' ';
        cout<<'\n';
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}