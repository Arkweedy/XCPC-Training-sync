#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

struct Node{
    int l,r,c;
};

struct Info{
    int x,l;
    ll ans;

    bool operator<(const Info &a)const{
        if(x != a.x)return x < a.x;
        else if(l < a.l)return l < a.l;
        return ans < a.ans;
    }
};


ll get(vector<Node>&a){
    if(a.empty())return 0;

    vector<Info>dp;
    dp.push_back({0,0,0});

    for(auto [l,r,c]:a){
        //cout<<l<<' '<<r<<' '<<c<<endl;
        vector<Info>ndp;
        for(int i=l;i<=r;i++){
            for(auto [x,L,ans]:dp){
                if(x == i){
                    ans -= 1ll * L * L;
                    ans += 1ll * (L+c) * (L+c);
                    ndp.push_back({x,L+c,ans});
                }else{
                    ndp.push_back({i,c,ans + 1ll * c * c});
                }
            }
        }
        dp.clear();
        sort(ndp.begin(),ndp.end());

        for(auto [x,L,ans]:ndp){
            if(!dp.empty() && dp.back().x == x && dp.back().ans <= ans){
                continue;
            }
            dp.push_back({x,L,ans});
        }
    }
    ll res = 1e18;
    for(auto [x,L,ans] : dp)res = min(res,ans);
    return res;
}

void solve()
{
    int n;cin>>n;
    vector<int>l(n),r(n);
    for(int i=0;i<n;i++)cin>>l[i];
    for(int i=0;i<n;i++)cin>>r[i];

    ll res = 0;
    vector<Node>stk;
    for(int i=0;i<n;){
        if(r[i] - l[i] + 1 > 2){
            res += get(stk);
            stk.clear();
            res++;
            i++;
            continue;
        }
        if(l[i] == r[i]){
            int j = i;
            while(j < n && l[j] == l[i] && r[j] == r[i]){
                j++;
            }
            stk.push_back({l[i],r[i],j-i});
            i = j;
        }else{
            stk.push_back({l[i],r[i],1});
            i++;
        }
    }

    res += get(stk);

    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
