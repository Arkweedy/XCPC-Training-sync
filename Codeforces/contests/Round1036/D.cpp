#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    if(k == 1){
        cout<<"Yes"<<endl;;
        return;
    }
    auto b = a;
    sort(b.begin(),b.end());
    int ma = b[k - 2];
    int l = lower_bound(b.begin(),b.end(),ma) - b.begin();
    int r = lower_bound(b.begin(),b.end(),ma + 1) - b.begin();
    int cnt = count(b.begin(),b.end(),ma);
    int les = k - 1 - l;
    int dec = cnt - les;
    //id in [0, l - 1] ->must choose
    //id in [l,r-1] ->choose able ,at least k - l
    //choose k-1 or k at totol
    vector<int>c;
    for(int i = 0;i < n;i++){
        if(a[i] <= ma){
            c.push_back(a[i]);
        }
    }
    //
    // cerr<<ma<<" "<<dec<<endl;
    // cerr<<l<<endl;

    auto check = [&](int x)->bool
    {
        int l = 0, r = c.size() - 1;
        int free = 0;
        int dec = 0;
        while(l < r){
            if(c[l] == c[r]){
                if(c[l] == ma){
                    free += 2;
                }
                l++,r--;
            }
            else{
                if(c[l] == ma){
                    l++;
                    dec++;
                }
                else if(c[r] == ma){
                    r--;
                    dec++;
                }else{
                    return false;
                }
            }
        }
        if(dec <= x){
            return true;
        }
        else{
            return false;
        }
    };

    if(check(dec)){
        cout<<"Yes"<<endl;
    }
    else{
        cout<<"No"<<endl;
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