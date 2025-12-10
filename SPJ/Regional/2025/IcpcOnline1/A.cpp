#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e5 + 10;


struct info{
    int id,p,t,st;
};

struct Node{
    ll id,cnt,t,op;
};

bool cmp(Node a,Node b){
    if(a.cnt != b.cnt)return a.cnt > b.cnt;
    else if(a.t!=b.t)return a.t < b.t;
    else return a.op > b.op;
}


void solve()
{
    int n;cin>>n;
    vector<info>a(n);
    map<string,int>ha;
    vector<string>na;
    int tot = 0;
    for(int i=0;i<n;i++){
        string s;cin>>s;
        if(!ha.count(s))ha[s] = tot++,na.push_back(s);
        a[i].id = ha[s];
        char c;cin>>c;
        a[i].p = c- 'A';
        cin>>a[i].t;
        cin>>s;
        if(s=="Rejected")a[i].st = -1;
        else if(s == "Accepted")a[i].st = 1;
        else a[i].st = 0;
    }
    sort(a.begin(),a.end(),[](info x,info y){
        return x.t<y.t;
    });
    
    vector<vector<int>>acl(tot,vector<int>(26));
    vector<vector<int>>acr(tot,vector<int>(26));
    vector<vector<int>>cul(tot,vector<int>(26));
    vector<vector<int>>cur(tot,vector<int>(26));
    vector<ll>ti(tot),cnt(tot);
    vector<ll>tm(tot),mx(tot);

    for(auto [id,p,t,st]:a){
        if(st == 1){
            if(!acl[id][p]){
                acl[id][p] = 1;
                ti[id] += t + cul[id][p];
                cnt[id]++;
            }
            if(!acr[id][p]){
                acr[id][p] = 1;
                tm[id] += t + cur[id][p];
                mx[id]++;
            }
        }
        else if(st == -1){
            cur[id][p] += 20;
            cul[id][p] += 20;
        }
        else{
            cul[id][p] += 20;
            if(!acr[id][p]){
                acr[id][p] = 1;
                tm[id] += t + cur[id][p];
                mx[id]++;
            }
        }
    }
    
    vector<Node>t;
    for(int i=0;i<tot;i++){
        t.push_back({i,cnt[i],ti[i],0});
        t.push_back({i,mx[i],tm[i],1});
    }
    
    sort(t.begin(),t.end(),cmp);
    
    vector<string>res;
    for(auto [id,cnt,_,op]:t){
        if(op==0)break;
        res.push_back(na[id]);
    }
    
    sort(res.begin(),res.end());
    
    for(auto s:res)cout<<s<<' ';
    cout<<'\n';
    
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
