#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    int l = 0, r = n - 1;
    int sta = 0;
    string s;
    while(l < r){
        if(a[l] < a[r]){
            if(sta){
                s += 'L';
                l++;
            }
            else{
                s += 'R';
                r--;
            }
        }
        else{
            if(!sta){
                s += 'L';
                l++;
            }
            else{
                s += 'R';
                r--;
            }
        }
        sta^=1;
    }
    s += 'L';
    cout<<s<<endl;
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