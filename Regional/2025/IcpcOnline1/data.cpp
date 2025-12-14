#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e5 + 10;


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
void solve()
{
    int n = rng()%5+1;
    cout<<n<<endl;
    for(int i=1;i<=n;i++)cout<<rng()%5+1<<" \n"[i==n];
    for(int i=2;i<=n;i++){
        int p = rng()%(i-1)+1;
        cout<<i<<' '<<p<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    while(t--){
        solve();
    }
    return 0;
}
