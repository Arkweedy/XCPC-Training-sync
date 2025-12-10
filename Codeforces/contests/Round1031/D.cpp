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
    vector<int>a(n),b(n);
    int ama = 0, bmi = 1145141919;
    for(int i = 0;i < n;i++){
        cin>>a[i];
        ama = max(ama,a[i]);
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
        bmi = min(bmi, b[i]);
    }
    
    
    
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>phead;
    priority_queue<pair<int,int>>ptail;
    ptail.push({0,0});
    int ans = 0;
    int out = 0;
    
    for(int i = 0;i < n;i++){
        phead.push(make_pair(a[i], i));
    }
    for(int i = 0;i < n;i++){
        //check b[i], a prefix min 0 - n - 1 - i
        while(!phead.empty() && phead.top().second > n - 1 - i){//rem i = 0, no empty
            phead.pop();
            out--;
        }
        if(phead.top().first > b[i]){
            cout<<n - i<<endl;
            return;
        }else{
            int ok = 0;
            pair<int,int>pr;
            if(!phead.empty()){
                ok = 1;
                pr = phead.top();
                phead.pop();
            }
            int mi = 1145141919;
            while(!phead.empty() && phead.top().second > n - 1 - i){
                phead.pop();
                out--;
            }
            if(!phead.empty()){
                mi = min(mi,phead.top().first);
            }
            if(!ptail.empty()){
                mi = min(mi,ptail.top().first);
            }
            if(mi > b[i]){
                cout<<n - i<<endl;
                return;
            }
            if(ok){
                phead.push(pr);
            }
        }
        ptail.push(make_pair(a[n - 1 - i],n - 1 - i));
        out++;
    }
    cout<<"nonono"<<endl;
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