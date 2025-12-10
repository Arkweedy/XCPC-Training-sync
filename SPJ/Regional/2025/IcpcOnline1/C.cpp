#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 2e5 + 10;


void solve()
{
    int n,m;cin>>n>>m;
    vector<pair<int,int>>v(n);
    for(int i=0;i<n;i++){
        auto &[r,l] = v[i];
        cin>>l>>r;
    }
    
    sort(v.begin(),v.end());
    
    int i = n -1;
    priority_queue<int>heap;
    int res = m;
    int cur = m;
    while(cur){
        
        while(i>=0 && v[i].first == cur){
            heap.push(v[i].second);
            i--;
        }
        
        while(!heap.empty() && heap.top() >= cur){
            heap.pop();
        }
        
        if(heap.empty()){
            if(i>=0)cur = v[i].first;
            else cur = 0;
        }
        else{
            res--;
            heap.pop();
            cur--;
        }
    }
    
    cout<<res<<'\n';

}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
