#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
constexpr int N =1e6+10;
//Create time: 2026.01.02 13:47:01

int n;
int a[N];
void get(int n)
{
    int p=1;
    vector<int> ve;
    if(n&1){
        for(int i=1;i<=n;i++) ve.push_back(i);
    }
    else {
        a[p++]=1;a[p++]=n-1;
        for(int i=1;i<=n;i++)
            if(i!=1&&i!=n-1) ve.push_back(i);
    }
//    for(auto p:ve) cerr<<p<<endl;
    int g=1;
    while(p<=n)
    {
        a[p++]=ve[g];
        g+=2;
        if(g>=ve.size())
        {
            g=0;
        }
    }
    a[n+1]=a[1];
    for(int i=1;i<=n;i++)
        assert(abs(a[i]-a[i+1])!=1);
    //for(int i=1;i<=n;i++) cerr<<a[i]<<' ';
}
void solve()
{
    cin>>n;
    if(n&1) {cout<<"NO\n";return ;}
    int k=n>>1;
    get(k);
    cout<<3*n/2<<'\n';
    n/=2;
    for(int i=1;i<=n;i++) 
    {
        int a=i,b=i+1;
        if(b>n) b=1;
        cout<<a<<' '<<b<<'\n';
        cout<<a+n<<' '<<b+n<<'\n';
    }
    for(int i=1;i<=n;i++) cout<<i<<' '<<a[i]+n<<'\n';
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
//    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}