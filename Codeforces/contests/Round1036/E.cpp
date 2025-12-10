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
    vector<ll>a(n);
    ll sum = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i];
    }
    if(sum % 2 == 1){
        cout<<-1<<endl;
        return;
    }
    for(int i = 0;i < n;i++){
        if(a[i] * 2 > sum){
            cout<<-1<<endl;
            return;
        }
    }

    vector<vector<ll>>ans;
    //cerr<<"begin:"<<endl;

    auto dec = [&](auto&&self, int l, int r, int round, ll more)->void
    {
        ans.push_back(vector<ll>(n));
        ll sum = 0;
        for(int i = l ;i <= r;i++){
            sum += a[i];
        }
        ll now = 0;
        int best = -1;
        for(int i = l;i <= r;i++){
            if(abs(sum - now * 2) >= abs(sum - (now + a[i]) * 2)){
                now += a[i];
                best = i;
            }
            else{
                break;
            }
        }
        
        //[l ,best] [best + 1, r]
        if(abs(sum - now * 2) <= more){
            //ok
            ll rem = sum - more;
            //rem / 2
            ll lrem = rem / 2, rrem = rem / 2;
            for(int i = l;i <= best;i++){
                if(lrem >= a[i]){
                    ans[round][i] = a[i];
                    lrem -= a[i];
                    a[i] = 0;
                }
                else{
                    ans[round][i] = lrem;
                    a[i] -= lrem;
                    lrem = 0;
                    break;
                }
            }
            for(int i = best + 1;i <= r;i++){
                if(rrem >= a[i]){
                    ans[round][i] = a[i];
                    rrem -= a[i];
                    a[i] = 0;
                }
                else{
                    ans[round][i] = rrem;
                    a[i] -= rrem;
                    rrem = 0;
                    break;
                }
            }

        }
        else{
            if(now * 2 < sum){//right more
                self(self, best + 1 ,r, round + 1, more + now);
            }
            else{
                self(self, l, best, round + 1, more + (sum - now));
            }

            ll rem = min(now, sum - now);
            ll lrem = rem , rrem = rem ;
            for(int i = l;i <= best;i++){
                if(lrem >= a[i]){
                    ans[round][i] = a[i];
                    lrem -= a[i];
                    a[i] = 0;
                }
                else{
                    ans[round][i] = lrem;
                    a[i] -= lrem;
                    lrem = 0;
                    break;
                }
            }
            for(int i = best + 1;i <= r;i++){
                if(rrem >= a[i]){
                    ans[round][i] = a[i];
                    rrem -= a[i];
                    a[i] = 0;
                }
                else{
                    ans[round][i] = rrem;
                    a[i] -= rrem;
                    rrem = 0;
                    break;
                }
            }
        }
        return;
    };

    dec(dec,0,n-1,0,0);

    cout<<ans.size()<<endl;
    for(int i = 0;i < ans.size();i++){
        for(int j = 0;j < n;j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }

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