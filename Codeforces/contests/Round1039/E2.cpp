#include<bits/extc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    pair<int,int>ansmax = {-1,-1};
    pair<int,int>ansmin = {-1,-1};
    auto checkmax = [&](int x)->bool
    {
        //cerr<<"check "<<x<<endl;
        vector<int>f(n);
        for(int i = 0;i < n;i++){
            if(a[i] >= x)f[i] = 1;
            else f[i] = -1;
        }
        // for(int i = 0; i < n;i++){
        //     cerr<<f[i]<<" ";
        // }
        // cerr<<endl;
        vector<int>pf(n);
        pf[0] = f[0];
        for(int i = 1;i < n;i++){
            pf[i] = pf[i - 1] + f[i];
        }
        int mi = 0;
        int mipos = 0;//l - 1
        for(int i = k - 1;i < n;i++){
            if(pf[i] - mi >= 0){
                ansmax = {mipos + 1,i + 1};
                return 1;
            }
            if(mi > pf[i - k + 1]){
                mi = pf[i - k + 1];
                mipos = i - k + 1 + 1;
            }
            
        }
        return false;
    };

    auto checkmin = [&](int x)->bool
    {
        vector<int>f(n);
        for(int i = 0;i < n;i++){
            if(a[i] <= x)f[i] = 1;
            else f[i] = -1;
        }
        
        vector<int>pf(n);
        pf[0] = f[0];
        for(int i = 1;i < n;i++){
            pf[i] = pf[i - 1] + f[i];
        }
        int mi = 0;
        int mipos = 0;//l - 1
        for(int i = k - 1;i < n;i++){
            if(pf[i] - mi >= 0){
                ansmin = {mipos + 1,i + 1};
                return 1;
            }
            if(mi > pf[i - k + 1]){
                mi = pf[i - k + 1];
                mipos = i - k + 1 + 1;
            }
            
        }
        return false;
    };

    int ma = -1,mi = -1;

    {
        int lmax = -1, rmax = n + 1;
        while(rmax - lmax > 1){
            int m = lmax + rmax >> 1;
            if(checkmax(m)){//m ok
                lmax = m;
            }
            else{
                rmax = m;
            }
        }
        ma = lmax;
    }

    {
        int lmin = -1, rmin = n + 1;
        while(rmin - lmin > 1){
            int m = lmin + rmin >> 1;
            if(checkmin(m)){//m ok
                rmin = m;
            }
            else{
                lmin = m;
            }
        }
        mi = rmin;
    }
    
    __gnu_pbds::tree<pair<int,int>, __gnu_pbds::null_type, less<pair<int,int>>,
                 __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update>
    trr;
    int tot = 0;
    vector<int>id(n);
    vector<pair<int,int>>ans(n + 1);
    int pami = mi, pama = ma;

    auto calc = [&](pair<int,int>rng)
    {
        int len = trr.size();
        int lval = trr.find_by_order((len - 1) / 2)->first,rval = trr.find_by_order((len - 1) / 2)->second;
        int assl = max(lval,pami),assr = min(rval,pama);
        for(int i = assl;i <= assr;i++){
            ans[i] = rng;
        }
        pami = max(lval,pami);
        pama = min(rval,pama);
    };

    

    
    if(ansmin.second < ansmax.second){//move r
        for(int i = ansmin.second + 1;i <= ansmax.second;i++){
            id[i] = tot++;
            trr.insert(make_pair(i,id[i]));
            calc({ansmin.first,i});
        }
        //
    }
    else{//move l

    }
    




    // int pma = ma, pmi = mi;
    
    // pair<int,int>range = {-1,-1};
    // auto getma = [&](int x)->bool
    // {
    //     vector<int>f(n);
    //     for(int i = 0;i < n;i++){
    //         if(a[i] >= x)f[i] = 1;
    //         else f[i] = -1;
    //     }
    //     vector<int>pf(n);
    //     pf[0] = f[0];
    //     for(int i = 1;i < n;i++){
    //         pf[i] = pf[i - 1] + f[i];
    //     }
    //     int mi = 0;
    //     int mipos = 0;//l - 1
    //     for(int i = k - 1;i < n;i++){
    //         if(pf[i] - mi >= 0){
    //             range = {mipos + 1,i + 1};
    //             return 1;
    //         }
    //         if(mi > pf[i - k + 1]){
    //             mi = pf[i - k + 1];
    //             mipos = i - k + 1 + 1;
    //         }
            
    //     }
    //     return false;
    // };

    // auto getmi = [&](int x)->bool
    // {
    //     vector<int>f(n);
    //     for(int i = 0;i < n;i++){
    //         if(a[i] <= x)f[i] = 1;
    //         else f[i] = -1;
    //     }
        
    //     vector<int>pf(n);
    //     pf[0] = f[0];
    //     for(int i = 1;i < n;i++){
    //         pf[i] = pf[i - 1] + f[i];
    //     }
    //     int mi = 0;
    //     int mipos = 0;//l - 1
    //     for(int i = k - 1;i < n;i++){
    //         if(pf[i] - mi >= 0){
    //             range = {mipos + 1,i + 1};
    //             return 1;
    //         }
    //         if(mi > pf[i - k + 1]){
    //             mi = pf[i - k + 1];
    //             mipos = i - k + 1 + 1;
    //         }
            
    //     }
    //     return false;
    // };

    // while(pma >= pmi){
    //     getma(pma);
    //     //cerr<<"get : "<<pma<<endl;
    //     //cerr<<range.first<<" "<<range.second<<endl;
    //     {
    //         vector<int>p;
    //         for(int i = range.first - 1;i <= range.second - 1;i++){
    //             p.push_back(a[i]);
    //         }
    //         sort(p.begin(),p.end());
    //         int len = p.size();
    //         int ml = p[(len - 1)/2], mr = p[len / 2];
    //         //cerr<<ml<<" "<<mr<<endl;
    //         for(int i = ml;i <= mr;i++){
    //             ans[i] = range;
    //         }
    //         pma = ml - 1;
    //     }
    //     getmi(pmi);
    //     {
    //         vector<int>p;
    //         for(int i = range.first - 1;i <= range.second - 1;i++){
    //             p.push_back(a[i]);
    //         }
    //         sort(p.begin(),p.end());
    //         int len = p.size();
    //         int ml = p[(len - 1)/2], mr = p[len / 2];
    //         //cerr<<ml<<" "<<mr<<endl;
    //         for(int i = ml;i <= mr;i++){
    //             ans[i] = range;
    //         }
    //         pmi = mr + 1;
    //     }
    // }
    
    int okcnt = 0;
    for(int i = mi;i <= ma;i++){
        if(ans[i] != make_pair(0,0))
            okcnt++;
    }
    cout<<okcnt<<'\n';
    //cerr<<mi<<" "<<ma<<endl;
    for(int i = mi;i <= ma;i++){
        if(ans[i] != make_pair(0,0)){
            cout<<i<<" "<<ans[i].first<<" "<<ans[i].second<<"\n";
        }
    }
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