#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
int K ;
int a[130];
void print(vector<int> ve)
{
    string s;
    for(auto p:ve) 
        {
            if(p) s+='1';
            else s+='0';
        }
    cout<<s<<endl;
}
void change()
{
    int b[130];
    memset(b,0,sizeof(b));
    for(int i=0;i<K;i++)
        if(!a[i])
        {
            int sum=0;
            //int sum=0;
            if(i&&a[i-1]) sum++;
            if(i<K-1&&a[i+1]) sum++;
            if(sum==1) b[i]=1;
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
    for(int t=1;t<=100;t++)
    {
        mp.clear();
        for(int i=0;i<K;i++)
        {
        a[i]= rng()%2;
        }
        vector<int> ve;
        for(int i=0;i<K;i++) ve.push_back(a[i]);
        mp[ve]=1;
    //print(ve);
    for(int i=2;i<=500;i++) 
    {
        change();
        vector<int> ve;
        for(int i=0;i<K;i++) ve.push_back(a[i]);
        //print(ve);
        //cout<<mp[ve]<<endl;
        if(mp[ve]&&sum(ve)&&i-mp[ve]<=2*K) 
        {
            print(ve);
        }
        mp[ve]=i;
    }
    }
    cout<<"Unlucky"<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}