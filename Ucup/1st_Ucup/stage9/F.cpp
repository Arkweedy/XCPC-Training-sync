#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;
int n,k;
// int check(vector<vector<int> > ve)
// {
//     int s=ve.size();
//     map<pair<int,int> ,int> mp;
//     for(int i=1;i<s;i++)
//     {
//         auto v=ve[i];
//         int m=v.size();
//         for(int ii=0;ii<m-1;ii+=1)
//         {
//             int a=ii,b=v[ii];
//         //    cerr<<a<<' '<<b<<' '<<i<<endl;
//             if(mp[{a,b}]&&mp[{a,b}]!=i+1) return 0;
//             mp[{a,b}]=i+1;mp[{b,a}]=i+1;
//         }
//     }
//     //cout<<1;return 1;
//     for(int i=0;i<n;i++)
//         for(int j=i+1;j<n;j++)
//             for(int ii=0;ii<n;ii++)
//                 for(int jj=ii+1;jj<n;jj++) {
//                     if(i!=ii&&i!=jj&&j!=ii&&j!=jj) 
//                     {
//                         //if(mp[{i,j}]!=mp[{ii,jj}] ) continue;
//                         if(mp[{i,jj}]!=mp[{j,ii}]) return 0;
//                         if(mp[{i,ii}]!=mp[{j,jj}]) return 0;
//                     }
//                 }
//     //for(auto [no,id]:mp) cerr<<no.first<<' '<<no.second<<' '<<id<<endl;
//     return 1;
// }
void solve()
{
    cin>>n>>k;
    vector<vector<int>> ans;
    int g=2;
    int cnt=0;
    vector<int> v;
    for(int i=0;i<n;i++) v.push_back(i);
    ans.push_back(v);
    while(cnt<k)
    {
        if(n%g) {cout<<"Impossible\n";return ;}
        for(int i=0;i<g/2;i++)
        {
            cnt++;
            if(cnt>k) break;
            vector<int> ve;
            ve.resize(n);
            int m=g/2;
            int t=(int)ans.size()-m;
            for(int i=0;i<m;i++) ve[i]=ans[t][i]+m;
            for(int i=m;i<g;i++) ve[i]=ve[i-m]-m;
            for(int j=g;j<n;j++) ve[j]=ve[j-g]+g;
            ans.push_back(ve);
        }
        g<<=1;
    }

    auto print=[&]()->void {
        for(auto v:ans)
        {
            if(v[0]==0) continue;
            for(int i=0;i<n;i++)
            {
                cout<<v[i]+1;
                if(i<n-1) cout<<' ';
                else cout<<'\n';
            }
        }
    };
    //assert(check(ans));
    print();
    
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
