#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;

void solve()
{
    int n,m;
    cin>>n>>m;
    vector<int>a(n),b(m);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int j = 0;j < m;j++){
        cin>>b[j];
    }
    sort(a.begin(),a.end(),greater<>());
    sort(b.begin(),b.end(),greater<>());
    
    ll dif = 0;
    for(int i = 0;i < m;i++){
        if(a[i] > b[i]){
            cout<<-1<<endl;
            return;
        }
        else{
            dif += b[i] - a[i];
        }
    }
    
    if(n - m < dif){
        cout<<-1<<endl;
        return;
    }
    
    vector<int>ans;
    
    multiset<int>st;
    for(int i = 0;i < n;i++){
        st.insert(a[i]);
    }
    
    int more = n - m - dif;
    for(int i = 0;i < more;i++){
        int x = *st.begin();
        ans.push_back(x);
        st.extract(x);
        st.insert(x + 1);
        st.erase(st.begin());
    }
    
    for(int i = m - 1; i >= 0;i--){
        while(a[i] < b[i]){
            int x = a[i];
            ans.push_back(x);
            a[i]++;
            if(st.find(x) == st.end()){
                cout<<-1<<endl;
                return;
            }
            st.extract(x);
            st.insert(x + 1);
            st.erase(st.begin());
        }
    }
    
    vector<int>c;
    for(auto e : st){
        c.push_back(e);
    }
    sort(c.begin(),c.end(),greater<>());
    if(b != c){
        cout<<-1<<endl;
        return;
    }
    
    cout<<ans.size()<<endl;
    for(int i = 0;i < ans.size();i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
