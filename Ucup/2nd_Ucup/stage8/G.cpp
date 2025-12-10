#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;

void solve()
{
    string s;
    cin>>s;
    list<char>ls;
    ls.insert(ls.begin(),' ');
    auto iter = ls.begin();
    string ans;
    auto add = [&](char c)->void
    {
        if(c == '('){
            ans += '(';
            ls.insert(next(iter),'(');
            iter++;
            ls.insert(next(iter),')');
        }
        else{
            ans += ')';
            ls.insert(next(iter),')');
            iter++;
        }
    };
    
    for(int i = 0;i < s.length();i++){
        if(next(iter) == ls.end()){
           
            add(s[i]);
        }
        else if(s[i] == *(next(iter))){
            if(s[i] == ')')
            ans += ')';
            iter++;
        }
        else{
            
            add(s[i]);
        }
        
    }
    
    
    
    if(next(iter) == ls.end()){
        cout<<ans<<"\n";
    }
    else{
        cout<<"impossible"<<"\n";
    }
    return;
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

