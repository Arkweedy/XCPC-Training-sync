#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

string get1(string& s){
    string res;
    res += s;
    res += ", ";
    res += s;
    res += " ";
    res += s;
    res += "ity";
    res += " ";
    res += s;
    
    return res;
}

string get2(string &s){
    string res;
    res += "i said ";
    res += s;
    res += ", ";
    res += s;
    res += " ";
    res += s;
    res += "ity";
    res += " ";
    res += s;
    return res;
}

void solve()
{
    vector<string>s;
    string t;
    while(getline(cin,t)){
        if(!t.empty())s.push_back(t);
    }
    int n = s.size();
    map<string,int>ha;
    int cur = 0,res = -1;
    string lst;
    for(int i=0;i+1<n;){
        auto ss = stringstream(s[i]);
        ss >> t;
        int len = t.size();
        if(t[len-1]!=','){
            cur = 0;
            lst.clear();
            i++;
            continue;
        }
        len--;
        t = t.substr(0,len);
        if(get1(t) == s[i] && get2(t) == s[i+1]){
            if(t == lst){
                cur++;
                res = max(res,cur * (8 * len + 23));
            }else{
                cur = 1;
                res = max(res,cur * (8 * len + 23));
                lst = t;
            }
            i+=2;
        }else{
            cur = 0;
            lst.clear();
            i++;
        }
    }
    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}