#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,q;
    //cin>>n>>q;
    string s;
    cin>>s;
    n = s.length();
    replace(s.begin(),s.end(),'L','0');
    replace(s.begin(),s.end(),'R','1');
    cerr<<s<<endl;
    auto ok = [&]()->bool
    {
        int x = count(s.begin(),s.end(),'0');
        return x == count(s.begin(),s.begin() + x,'0');
    };
    int cnt = 0;
    while(!ok()){
        for(int i = 0;i < n;i++){
            if(s[i] == '1' && s[i + 1] == '0'){
                swap(s[i],s[i + 1]);
                i++;
            }
        }
        cnt++;
        cerr<<s<<endl;
    }
    cout<<cnt<<endl;
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