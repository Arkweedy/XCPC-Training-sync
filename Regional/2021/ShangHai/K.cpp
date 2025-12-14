#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int X = 10, Y = 20;

constexpr int N = 1e5 + 10;
int K ;
int a[130];
void print(vector<int> ve)
{
    int cnt=0;
    for(auto p:ve) 
    {
        cnt++;
        cout<<p;
        if(cnt==20) cout<<"LLL";
    }
    cout<<endl;
}
void change()
{
    int b[130];
    memcpy(b,a,sizeof(b));
    for(int i=0;i<K;i++)
        if(a[i])
        {
            for(int j=i-1;j<=i+1;j++)
                if(j>=0&&j<K) b[j]^=1;
        }
    memcpy(a,b,sizeof(b));
}
map<vector<int> ,int> mp;
int sum(vector<int> ve)
{
    int ans=0;
    for(auto p:ve) ans+=p;
    return ans;
}

void solve()
{
    cin>>K;
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    for(int t=1;t<=1;t++)
    {
        mp.clear();
        for(int i=0;i<K;i++)
        {
        a[i]= rng()%2;
        //a[i]=0;
        }
        vector<int> ve;
        for(int i=0;i<K;i++) ve.push_back(a[i]);
        mp[ve]=1;
    //print();
    for(int i=2;i<=20;i++) 
    {


        change();
        vector<int> ve;
        for(int i=0;i<10;i++) ve.push_back(a[i]);
        print(ve);
        if(mp[ve]&&sum(ve)) 
        {
            print(ve);
        
            cout<<i-mp[ve]<<' ';
            return ;
        }
        mp[ve]=i;
    }
    }
    cout<<"Unlucky";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int tt = 1;
//    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}