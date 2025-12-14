#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 5e5 + 10;

string s,t;

int ne[N][20],tot,cnt[N][20],st[N][20];
int l[20],r[20],nxt[N],v[20];

void kmp(string &s,int op){
    int len  =s.size()-1;
    for(int i=2,j=0;i<s.size();i++){
        while(j && s[j+1] != s[i])j = nxt[j];
        if(s[j+1] == s[i])j++;
        nxt[i] = j;
    }
   
    for(int i=0,j = 0;i<t.size();i++){
        //cerr<<i<<endl;
        while(j && s[j+1] != t[i])j = nxt[j];
        if(s[j+1] == t[i])j++;
        
        if(j == len){
            st[i-len+1][op] = 1;
            //cout<<i<<' '<<op<<endl;
            j = nxt[j];
        }
    }
}

void solve()
{
    cin>>s>>t;
    bool flg = 0;
    int c = 0;

    for(int i=0;i<s.size();){
        if(s[i] == '*'){
            i++;
            c++;
            continue;
        }
        int j = i;
        while(j<s.size() && s[j]!='*')j++;
        l[tot] = i,r[tot] = j - 1;
        v[tot] = j - i;
        string res;
        res += ' ';
        for(int k=i;k<j;k++)res += s[k];
        kmp(res,tot);
        tot++;
        i = j;
    }
    
    if(s[s.size()-1] == '*')flg = 1;
    int n = t.size();

    for(int j=0;j<tot;j++)ne[n][j] = n;
    
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<tot;j++){
            ne[i][j] = ne[i+1][j];
            if(st[i][j])ne[i][j] = i;
        }

        for(int j=0;j<tot;j++){
            cnt[i][j] = cnt[i+1][j] + st[i][j];
        }
    }
    ll res = 0;
    if(tot==0){
        cout<<1ll*n*(n+1)/2<<'\n';
        return;
    }
    else{
        for(int i=0;i<n;i++){
            if(s[0] == '*'){
                int p = i;
                for(int j=0;j<tot-1;j++){
                    p = ne[p][j] + v[j];
                    p = min(p,n);
                }
                if(!flg)res += cnt[p][tot-1];
                else {
                    p = min(ne[p][tot-1]+v[tot-1]-1,n);
                    res += n - p;
                }
            }
            else if(st[i][0]){
                int p = i;
                for(int j=0;j<tot-1;j++){
                    p = ne[p][j] + v[j];
                    p = min(p,n);
                }
                if(c == 0)res++;
                else if(!flg)res += cnt[p][tot-1];
                else {
                    p = min(ne[p][tot-1]+v[tot-1]-1,n);
                    res += n - p;
                    
                }
            }
        }
    }
    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}
