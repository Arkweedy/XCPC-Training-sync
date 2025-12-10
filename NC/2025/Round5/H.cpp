#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    auto calc = [&](int l, int r)->int
    {
        set<int>st;
        for(int i = l;i <= r;i++){
            st.insert(a[i]);
        }
        int res = *st.begin();
        for(auto x : st){
            if(res == x)res++;
            else break;
        }
        return res;
    };
    ll ans = 0;
    for(int i = 0;i < n;i++){
        for(int j = i;j < n;j++){
            ans += calc(i,j);
            cerr<<i<<" "<<j<<" += "<<calc(i,j)<<endl;
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
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}