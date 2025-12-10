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
    vector<int>st;
    for(int i = 0;i < n;i++){
        if(st.empty() || a[i] > st.back()){
            st.push_back(a[i]);
        }
        else{
            int p = lower_bound(st.begin(),st.end(),a[i]) - st.begin();
            st[p] = a[i];
        }
    }
    int p = 0;
    vector<int>ans;
    for(int i = 0;i < n;i++){
        if(p == st.size())break;
        if(a[i] == st[p]){
            ans.push_back(a[i]);
            p++;
        }
        else{
            int q = lower_bound(st.begin(),st.end(),a[i]) - st.begin();
            if(q == p + 1){
                while(a[i] != st[p])i++;
                p++;
            }
        }
    }
    cout<<ans.size()<<endl;
    for(int i = 0; i< ans.size();i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
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