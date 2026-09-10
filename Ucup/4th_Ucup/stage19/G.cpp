#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;
struct team{
    team(){
        cnt=time=0;
        memset(a,0,sizeof(a));
        t=tt=p=0;
    }
    string s;
    int cnt,time;
    int a[26];
    int t,tt;
    int p;
    int id;
};
bool operator <(team a,team b){
    if(a.cnt!=b.cnt) return a.cnt>b.cnt;
    if(a.time!=b.time) return a.time<b.time;
    return a.tt<b.tt;
}
struct problem{
    int c;
    int t;
    int tt;
    int tru;
};
struct answer{
    string s;
    int t;int tt;
};
bool operator <(answer a,answer b){
    return a.tt<b.tt;
}
void print(int t){
    cout<<t/60<<':';
    t%=60;
    if(t<10) cout<<0;
    cout<<t<<'\n';
}
void solve()
{
    int p,n;cin>>p>>n;
    vector<team>te(n+1);
    vector<vector<problem> > pr(n+1);
    int cnt=0;
    map<string ,int>  mp;
    for(int i=1;i<=n;i++) {
        string s;cin>>s;
        if(!mp[s]) mp[s]=++cnt;
        int g=mp[s];
        te[g].s=s;te[g].id=g;
        char c;cin>>c;
        int cc=c-'A';
        int h;cin>>h;char ccc;cin>>ccc;
        int ss;cin>>ss;
        int t=h*60+ss;
        cin>>s;
        int tru=0;
        if(s=="OK") tru=1;
        pr[g].push_back({cc,t,i,tru});
        if(te[g].a[cc]==1) continue;
        if(tru==1){
            te[g].cnt++;
            te[g].tt=i;
            te[g].t=t;
            te[g].time+=20*(-te[g].a[cc])+t;
            te[g].a[cc]=1;
        }
        else te[g].a[cc]--;
    }
    vector<team> ve;
    for(int i=1;i<=cnt;i++) ve.push_back(te[i]);
    sort(ve.begin(),ve.end());
    for(int i=0;i<ve.size();i++) {
        int s=ve[i].id;
        te[s].p=i;
    }
    auto com=ve[12];
    //cout<<com.cnt<<endl;
    vector<answer> ans;
    for(int i=1;i<=cnt;i++){
        if(te[i].p>=12) continue;
        int a[26],cnt=0,time=0,tt=-1;
        auto my=te[i];
        
        memset(a,0,sizeof(a));

        for(int j=0;j<pr[i].size();j++){
            int c=pr[i][j].c,tru=pr[i][j].tru,t=pr[i][j].t,ttt=pr[i][j].tt;
            if(a[c]==1) continue;
            if(tru){
                cnt++;
                time+=20*(-a[c])+t;
                tt=ttt;
                a[c]=1;
                my.cnt=cnt;
                my.time=time;
                my.tt=tt;
                if(my<com){
                    ans.push_back({te[i].s,t,ttt});
                    break;
                }
            }
            else {
                a[c]--;
            }
        }


    }
    sort(ans.begin(),ans.end());
    for(auto [s,t,tt]:ans){
        cout<<s<<' ';
        print(t);
    //    cout<<t/60<<":"<<t%60<<'\n';
    }

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
