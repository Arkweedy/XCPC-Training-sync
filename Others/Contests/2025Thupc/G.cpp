#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
#define N 500009
using namespace std;

string cmin(const string &a,const string & b){
    if(a.size() != b.size()){
        if(a.size() < b.size())return a;
        else return b;
    }
    for(int i=0;i<a.size();i++){
        if(a[i] != b[i]){
            if(a[i] < b[i])return a;
            else return b;
        }
    }
    return a;
}

string operator+(const string &a,const string & b){
    if(a.empty() || b.empty())return a + b;
    string res;
    int i = (int)a.size() - 1,j = (int)b.size() - 1;
    int c = 0;
    while(i >= 0 || j >= 0){
        if(i>=0)c += a[i] - '0';
        if(j>=0)c += b[j] - '0';
        i--,j--;
        res += char('0' + c % 2);
        c/=2;
    }
    if(c)res += '1';
    reverse(res.begin(),res.end());
    return res;
}

void solve()
{
    int n;cin>>n;
    string s;cin>>s;

    int cnt=  0;
    for(auto c:s)cnt += s[i] - '0';

    if(cnt <= 1){
        cout<<cnt<<'\n';
        return;
    }

    auto get = [&](int c,int i,int x,int y){
        if(x <0 || y < 0)return s;
        assert(n - i - 1 == x + y)
        string a = string(c,'1');
        string b;
        while(i<n){
            int c = s[i] - '0';
            if(c == 0){
                if(x >= y){
                    a += '0';
                    x--;
                }else{
                    b += '0';
                    y--;
                }
            }else{
                if(x >= y){
                    b += '1';
                    y--;
                }else{
                    a += '0';
                    x--;
                }
            }
            i++;
        }
        return a + b;
    };

    int cur = 0;
    int t = 0,cnt = 0;
    for(int i=0;i<n;i++){
        if(s[i] == '1'){
            if(n-i-1>=cur){
                t = i;
                cnt = cur + 1;
            }
            cur++;
        }
    }
    string res = s;
    cur = 0;
    for(int i=t;i>=0;i--){
        if(s[i] == '1'){
            int sz = n - 1 - i + cnt;
            int x = sz/2,y = (sz+1)/2;
            string ans = cmin(get(cnt,i+1,x-cnt,y),get(cnt,i+1,x-cnt,y));
            res = cmin(res,ans);
            cnt--,cur++;
            if(cur == 100)break;
        }
        
    }

    cout<<res<<'\n';
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