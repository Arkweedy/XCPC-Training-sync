#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.31 15:28:20

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    auto b = a;
    b.erase(unique(b.begin(),b.end()),b.end());
    int m = b.size();
    vector<int>c(m);
    for(int i = 0;i < n;i++){
        int p = lower_bound(b.begin(),b.end(),a[i]) - b.begin();
        c[p]++;
    }
    vector<int>pc = c;
    for(int i = 1;i < m;i++){
        pc[i] += pc[i - 1];
    }
    //[l,r]

    auto get = [&](int l, int r)->int
    {
        if(l > r)return 0;
        int res = 0;
        res += pc[r];
        if(l > 0)res -= pc[l - 1];
        return res;
    };

    int ans = 0;
    for(int i = 0;i < m;i++){
        int r = m - 1;
        for(int l = 0;l <= i;l++){
            int rv = 2 * b[i] - b[l];
            while(rv < b[r])r--;
            if(rv > b[r])continue;
            //[l,r]->m
            int cl = get(l,i - 1), cm = get(i,i),cr = get(i + 1, r);
            if(abs(cl - cr) < cm){
                ans = max(ans, cl + cm + cr);
            }
            else{
                if(cl < cr){
                    ans = max(ans, (cl + cm) * 2);
                }
                else{
                    ans = max(ans,(cm + cr) * 2 - 1);
                }
                //ans = max(ans, min( min(cl + cm, cr) * 2, min(cl, cm + cr) * 2 - 1));
                //if cl == cm + cr ->WA ?
            }
        }
    }
    cout<<ans<<endl;
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