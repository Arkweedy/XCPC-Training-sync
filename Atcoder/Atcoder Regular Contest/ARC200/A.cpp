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
    vector<int>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int  i = 0;i <n;i++){
        cin>>b[i];
    }
    
    vector<array<int,3>>t(n);
    for(int i = 0;i < n;i++){
        if(a[i] != 0 || b[i] != 0)
            t[i] = {a[i],b[i],i};
    }
    sort(t.begin(),t.end(),[&](const array<int,3>&i,const array<int,3>& j)->bool
    {
        return 1ll * i[0] * j[1] > 1ll * j[0] * i[1];
    });

    auto check = [&](vector<int>k)->bool
    {
        ll x = 0, y = 0;
        int ok = 1;
        for(int i = 0;i < n;i++){
            x += 1ll * a[i] * k[i];
            y += 1ll * b[i] * k[i];
            if(abs(k[i]) > 1e8)ok = 0;
        }
        cerr<<x<<" "<<y<<endl;
        return x > 0 && y < 0 && ok;
    };

    int l = 0,r = n - 1;
    while(a[l] == 0 && b[l] == 0){
        l++;
    }
    while(a[r] == 0 && b[r] == 0){
        r--;
    }
    
    
    if(1ll * t[l][0] * t[r][1] == 1ll * t[l][1] * t[r][0]){
        cout<<"No"<<endl;
    }else{
        vector<int>ans(n);
        
        
        ans[t[l][2]] = t[r][0];
        ans[t[r][2]] = -t[l][0];
        while(abs(ans[t[l][2]]) < 4e7 && abs(ans[t[r][2]]) < 4e7){
            ans[t[l][2]] *= 2;
            ans[t[r][2]] *= 2;
        }
        ans[t[l][2]]++;
        cout<<"Yes"<<endl;
        for(int i = 0;i < n;i++){
            cout<<ans[i]<<" ";
        }
        cout<<endl;
        // if(check(ans)){
        //     cerr<<"AC"<<endl;
        // }else{
        //     cerr<<"WA"<<endl;
        // }
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