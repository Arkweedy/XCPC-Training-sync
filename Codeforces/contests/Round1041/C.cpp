#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, k;
    cin>>n>>k;
    vector<ll>a(n),b(n);
    vector<pair<ll,ll>>pr(n);
    ll sum = 0;
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
        pr[i] = make_pair(a[i],b[i]);
        sum += abs(a[i] - b[i]);
    }
    sort(pr.begin(),pr.end());
    //cerr<<"check"<<endl;
    for(int i = 0;i < n - 1;i++){
        if(max(pr[i].first,pr[i].second) > min(pr[i + 1].first,pr[i + 1].second)){
            //cerr<<i<<" neg"<<endl;
            cout<<sum<<endl;
            return;
        }
    }
    
    //ordered
    ll mind = LLONG_MAX;
    for(int i = 0;i < n - 1;i++){
        vector<ll>arr = {pr[i].first,pr[i].second,pr[i + 1].first,pr[i + 1].second};
        sort(arr.begin(),arr.end());
        ll delta = (arr[3] + arr[2] - arr[1] - arr[0]) - abs(pr[i].first - pr[i].second) - abs(pr[i + 1].first - pr[i + 1].second);
        //cerr<<arr[0]<<" "<<arr[1]<<" "<<arr[2]<<" "<<arr[3]<<endl;
        //cerr<<"delta "<<i<<" = "<<delta<<endl;
        mind = min(mind, delta);
    }
    cout<<sum + mind <<endl;
    return;

    
    // set<pair<int,int>>st;
    // for(int i = 0;i < n;i++){
    //     st.insert(make_pair(abs(a[i] - b[i]), i));
    // }
    // auto update = [&](bool chs)->void
    // {
    //     int x, y;
    //     if(chs){//small -> big
    //         x = st.begin() -> second;
    //         st.erase(st.begin());
    //         y = st.begin() -> second;
    //         st.erase(st.begin());
    //     }
    //     else{
    //         x = prev(st.end()) -> second;
    //         st.erase(prev(st.end()));
    //         y = prev(st.end()) -> second;
    //         st.erase(prev(st.end()));
    //     }
    //     vector<int>arr = {a[x],b[x],a[y],b[y]};
    //     sort(arr.begin(),arr.end());
    //     if(chs){
    //         a[x] = arr[0];
    //         b[x] = arr[3];
    //         a[y] = arr[1];
    //         b[y] = arr[2];
    //         st.insert(make_pair(abs(a[x] - b[x]), x));
    //         st.insert(make_pair(abs(a[y] - b[y]), y));
    //     }
    //     else{
    //         a[x] = arr[0];
    //         b[x] = arr[1];
    //         a[y] = arr[2];
    //         b[y] = arr[3];
    //         st.insert(make_pair(abs(a[x] - b[x]), x));
    //         st.insert(make_pair(abs(a[y] - b[y]), y));
    //     }
    // };

    // for(int i = 0;i < n;i++){
    //     update(0);
    // }
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