#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 1e6+5;

void solve()
{
    int n, q;
    cin>>n>>q;
    bitset<N>s;
    string stmp;
    cin>>stmp;
    for(int i = 0;i < n;i++){
        if(stmp[i] == '1'){
            s.flip(i);
        }
    }
    
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;

    auto all = [&]()->void
    {
        vector<pair<int,int>>buf;
        pair<int,int>pr = {0,-1};
        while(!pq.empty()){
            auto [l,r] = pq.top();
            pq.pop();
            // l >= pr.first
            if(l > pr.second){
                if(pr.second >= 0)buf.push_back(pr);
                pr = make_pair(l,r);
            }
            else{//xiang jiao
                if(pr.second > r){
                    pq.push(make_pair(r + 1, pr.second));
                    pr.second = l - 1;
                }
                else{
                    if(r != pr.second){
                        pq.push(make_pair(pr.second + 1, r));
                    }
                    pr.second = l - 1;
                }
            }
        }
        if(pr.second >= 0)buf.push_back(pr);
        // for(auto pir : buf){
        //     cerr<<pir.first + 1<<" "<<pir.second + 1<<endl;
        // }
        for(int i = 0;i < buf.size();i++){
            for(int j = buf[i].first;j <= buf[i].second;j++){
                s.flip(j);
            }
        }
    };


    
    
    while(q--){
        int op;
        cin>>op;
        if(op == 1){
            int l, r;
            cin>>l>>r;
            l--,r--;
            pq.push({l,r});
        }
        else{
            int l, a, b;
            cin>>l>>a>>b;
            a--;
            b--;
           
            all();
            bitset<N>as = s >> a, bs = s >> b;
            as ^= bs;
            as[l] = 1;
           
            ll ans = 0;
            for(int p = -1;p < l;){
                int nxt = as._Find_next(p);
                ll len = nxt - p - 1;
                ans += len * (len + 1) / 2;
                p = nxt;
            }
            cout<<ans<<endl;
        }
    }
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