#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    string s;
    //cin>>s;
    int offset = 0;
    for(int i = 0;i < 8;i++){
        cerr<<s.length()<<",";
        s += '#';
        s += ')';
        int more = (1 << i) - 1;
        offset += (more + 1) * more / 2;
        cerr<<"offset += "<<(more + 1) * more / 2<<endl;
        for(int j = 0;j < ((1 << i)) - 1;j++){
            s += "()";
        }
        s +=')';
    }
    int n = s.size();
    auto check = [&](string a)->int
    {
        int res = 0;
        for(int i = 0;i < n;i++){
            for(int j = i;j < n;j++){
                int x = 0;
                for(int k = i;k <= j;k++){
                    if(a[k] == ')')x--;
                    else if(a[k] == '(') x++;
                    else{
                        x = -1;
                        break;
                    }
                    if(x < 0)break;
                }
                
                if(x==0)res++;
            }
        }
        return res;
    };
    //cerr<<check(s)<<endl;
    cerr<<endl;
    cout<<s<<endl;
    cout<<s.length()<<endl;
    //cerr<<offset<<endl;
    s[0] = s[3] = s[8] = '(';
    cout<<check(s)<<endl;
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