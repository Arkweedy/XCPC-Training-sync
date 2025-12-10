#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    string s;
    int offset = 1;
    int len = 0;
    auto calc = [&](int len)->int
    {
        int l = len / 2, r = (len - 1) / 2;
        return (len + 1) * len / 2 - (l + 1) * l / 2 - (r + 1) * r / 2;
    };
    for(int i = 0;i < 13;i++){
        int all = len + 1;
        while(calc(all) < offset)all++;
        len = all;
        offset += calc(len);
        int l = len / 2, r = (len - 1) / 2;
        for(int j = 0;j < l;j++){
            s += "()";
        }
        
        cerr<<calc(len)<<",";
        s += '#';
        s += ')';
        for(int j = 0;j < r;j++){
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
    cout<<check(s)<<endl;
    //cout<<offset<<endl;
    cout<<s<<endl;
    cout<<s.length()<<endl;
  
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