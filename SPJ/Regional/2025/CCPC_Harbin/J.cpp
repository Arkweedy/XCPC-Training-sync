#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int P = 1e9 + 7;

vector<int>manacher(string & s){
    string t = "#";
    for(auto c : s){
        t += c;
        t += '#';
    }
    //cout<<t<<endl;
    int n = t.size();
    vector<int>r(n);

    for(int i=0,j=0;i<n;i++){
        if(2 *j -i>=0 && j + r[j] > i){
            r[i] = min(r[2*j-i],j + r[j]-i);
        }
        while(i - r[i] >= 0 && i + r[i] < n && t[i-r[i]] == t[i+r[i]])r[i]++;

        if(i + r[i] > j + r[j]){
            j = i;
        }
    }

    // for(int i=0;i<n;i++)cout<<r[i]<<' ';
    // cout<<endl;
    return r;
}

struct info{
    int i,j;
    int len = 0;
};

info max(const info & a,const info &b){
    if(a.len < b.len){
        return b;
    }else{
        return a;
    }
}

void solve()
{
    int n;cin>>n;
    string s,t;cin>>s;

    info res = {0,0,1};

    for(auto c:s){
        if(c == 'o')t += c;
        else if(c == 'v')t += c;
        else t += "vv";
    }

    auto r = manacher(t);
    int m = r.size();
    
    vector<int>be(t.size(),-1);

    vector<int>ne(t.size(),t.size()),pre(t.size(),-1);

    for(int i=0;i<t.size();i++){
        if(t[i] == 'o')pre[i] = i;
        else if(i)pre[i] = pre[i-1];
    }

    for(int i=(int)t.size()-1;i>=0;i--){
        if(t[i] == 'o')ne[i] = i;
        else if(i + 1 < t.size())ne[i] = ne[i+1];
    }

    int cur = 0;

    for(int i=0;i<n;i++){
        if(s[i] == 'o'){
            be[cur] = i;
            cur++;
        }else if(s[i] == 'v'){
            be[cur] = i;
            cur++;
        }else{
            be[cur] = be[cur+1] = i;
            cur += 2;
        }
    }

    for(int i=0;i<n;){
        int j = i;

        auto check = [&](char a,char b)->bool
        {
            if(a == 'o' || b == 'o')return a == b;
            else return 1;
        };

        while(j<n && check(s[i],s[j]))j++;
        info ans = {i,j-1,j-i};
        res = max(res,ans);
        i = j;
    }
    
    vector<int>st(t.size() + 1,-1);
    for(int i=0;i<m;i++){
        if(r[i] <= 1)continue;
        int x,y;
        if(i&1){
            int p = i / 2;
            x = p - (r[i]-1)/2;
            y = p + (r[i]-1)/2;
        }else{
            int p = i / 2; 
            x = p - (r[i]-1)/2;
            y = p + (r[i]-1)/2-1;
        }
        
        if(ne[x] > y)continue;
        
        int u = be[ne[x]],v = be[pre[y]];
        int j = v + 1,val = 0;
        
        info ans = {u,v,v-u+1};

        res = max(res,ans);

        while(j < n && s[j] != 'o'){
            val += s[j] == 'w' ? 2 : 1;
            st[val] = j;
            j++;
        }

        j = u - 1,val = 0;
        while(j >= 0 && s[j] != 'o'){
            val += s[j] == 'w' ? 2 : 1;
            if(st[val] != -1){
                info ans = {j,st[val],st[val]-j+1};
                res = max(res,ans);
            }
            j--;
        }

        j = v + 1,val = 0;
        while(j < n && s[j] != 'o'){
            val += s[j] == 'w' ? 2 : 1;
            st[val] = -1;
            j++;
        }
    }

    for(int i=res.i;i<=res.j;i++)cout<<s[i];
    cout<<'\n';

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}