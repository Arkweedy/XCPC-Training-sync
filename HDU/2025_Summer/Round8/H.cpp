#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, m;
    cin>>n>>m;
    string s, t;
    cin>>s>>t;
    string nt;
    if(count(t.begin(),t.end(), '1') == 0){
        if(count(s.begin(),s.end(),'1') == 0){
            cout<<0<<"\n";
        }
        else{
            cout<<-1<<"\n";
        }
        return;
    }
    int p = 0;
    for(int i = 0;i < m;i++){
        if(t[i] == '1'){
            p = i;
            break;
        }
    }
    for(int i = 0;i < p;i++){
        if(s[i] == '1'){
            cout<<-1<<"\n";
            return;
        }
    }
    int ans = 0;
    for(int i = p;i - p + m - 1 < n;i++){
        if(s[i] == '1'){
            for(int j = p;j < m;j++){
                s[i + j - p] = ((s[i + j - p] - '0') ^ (t[j] - '0')) + '0';
            }
            ans++;
        }
        //cout<<s<<endl;
    }
    for(int i = 0;i < m;i++){
        if(s[n - i - 1] == '1'){
            cout<<-1<<"\n";
            return;
        }
    }
    cout<<ans<<"\n";
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