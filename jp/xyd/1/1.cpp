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
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
    }
    stack<int>st;
    int pa = 0, pb = 0;
    while(pa < n || pb < n){
        if(st.empty() || st.top() != b[pb]){
            if(pa == n)break;
            else st.push(a[pa++]);
        }
        else{
            st.pop();
            b[pb++];
        }
    }
    if(pb != n){
        cout<<"No"<<endl;
    }
    else{
        cout<<"Yes"<<endl;
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