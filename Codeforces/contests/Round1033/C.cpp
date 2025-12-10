#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll n,m;
    cin>>n>>m;
    if(m > n * (n + 1) / 2 || m < n){
        cout<<-1<<endl;
        return;
    }
    int root = 0;
    int sum = 0;
    vector<int>fa(n + 1);
    for(int i = 0;i <= n;i++){
        if(sum + (n - root) < m){
            sum += n - root;
            root++;
        }else{
            break;
        }
    }
    sum += n - root;
    root++;
    fa[root] = -1;
    for(int i = 1;i <= n;i++){
        if(i != root){
            fa[i] = root;
        }
    }
    int p = root + 1;
    while(sum > m){
        fa[p++] = root - 1;
        sum--;
    }

    cout<<root<<endl;
    for(int i = 1;i <= n;i++){
        if(i != root){
            cout<<i<<" "<<fa[i]<<endl;
        }
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}