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
    //find 2l 2r
    auto ask = [&](vector<int>a)->int
    {
        cout<<"? "<<a.size()<<" ";
        for(int i = 0;i < a.size();i++){
            cout<<a[i]<<" ";
        }
        cout<<endl;
        int res;
        cin>>res;
        return res;
    };

    //binary search on pair
    //add single 
    //if reach target ->ask it
    //choose one
    int l = 2, r = n + 1;
    while(r - l > 1){
        vector<int>a;
        a.push_back(1);
        int m = l + r >> 1;
        for(int i = l;i <= m;i++){
            a.push_back(i);
        }
        int resx = ask(a);
        if(resx == 0){
            reverse(a.begin(),a.end());
            int resy = ask(a);
            if(resy == 0){
                l = m;
            }
            else{
                r = m;
            }
        }
        else{
            r = m;
        }
    }

    int lp = 1, rp = l;
    if(ask({lp,rp}) == 0){
        swap(lp,rp);
    }


    int len = 8;
    string ss = "#))#)())#)()()())#)()()()()()()())#)()()()()()()()()()()()()()()())#)()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()())#)()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()())#)()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()())";
    vector<int>insertpos = {0,3,8,17,34,67,132,261};
    int offset = 10795;
    string ans(n,'0');

    if(n < len){
        for(int i = 1;i <= n;i++){
            int res = ask({lp,i});
            if(res > 0)ans[i] = ')';
            else ans[i] = '(';
        }
        cout<<"! "<<ans<<endl;
        return;
    }

    auto ask_range = [&](int l)->int
    {
        vector<int>askarr;
        int p = l;
        for(auto ch : ss){
            if(ch == '(')askarr.push_back(lp);
            else if(ch == ')')askarr.push_back(rp);
            else askarr.push_back(p++);
        }
        int res = ask(askarr);
        return res;
    };

    
    for(int i = 1;i <= n;i+=len){
        int res = ask_range(i);
        for(int j = 0;j < len;j++){
            if(res >> j & 1)ans[i + j] = ')';
            else ans[i + j] = '(';
        }
    }
    int base = n + 1 - len;
    int res = ask_range(base);
    for(int i = 0;i < len;i++){
        if(res >> i & 1)ans[i + base] = ')';
        else ans[i + base] = '(';
    }

    cout<<"! "<<ans<<endl;
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