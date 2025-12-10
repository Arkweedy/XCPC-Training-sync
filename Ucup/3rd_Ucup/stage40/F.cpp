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
    iota(a.begin(),a.end(),1);
    random_shuffle(a.begin(),a.end());
    // int n;
    // cin>>n;
    // vector<int>a(n);
    int id = -1;
    for(int i = 0;i < n;i++){
        //cin>>a[i];
        if(a[i] == 1)id = i;

    }

    vector<array<int,3>>ans;

    auto add = [&](int x, int y)->void
    {
        a[x] += a[y];
        ans.push_back({x,y,1});
        assert(a[x] <= n);
    };

    auto sub = [&](int x, int y)->void
    {
        a[x] -= a[y];
        ans.push_back({x,y,-1});
        assert(a[x] > 0);
    };



    int l = 0, r = 0;
    if(id == 0){
        while(a[id + 1] != 1){
            sub(id + 1, id);
        }
        l = id - 1, r = id + 2;
    }
    else{
        while(a[id - 1] != 1){
            sub(id - 1, id);
        }
        l = id - 2, r = id + 1;
    }

    auto nxt = [&](int p)->void
    {
        add(p, p + 1);
        add(p + 1,p);
    };

    auto prv = [&](int p)->void
    {
        sub(p + 1, p);
        sub(p, p + 1);
    };

    for(int i = l;i >= 0;i--){
        while(a[i + 1] + 2 * a[i + 2] < a[i]){
            nxt(i + 1);
        }
        while(a[i + 1] != 1){
            while(a[i] > a[i + 1]){
                sub(i, i + 1);
            }
            prv(i + 1);
        }
        while(a[i] != 1)sub(i,i + 1);
    }

    for(int i = r;i < n;i++){
        while(2 * a[i - 1] + a[i - 2] < a[i]){
            nxt(i - 2);
        }
        while(a[i - 1] != 1){
            while(a[i] > a[i - 1]){
                sub(i, i - 1);
            }
            prv(i - 2);
        }
        while(a[i] != 1)sub(i,i-1);
    }

    for(int i = 0;i < n - 1;i++){
        add(i + 1, i);
    }

    cout<<ans.size()<<endl;
    for(int i = 0;i < ans.size();i++){
        cout<<ans[i][0] + 1<<" "<<(ans[i][2] == 1 ? '+' : '-')<<" "<<ans[i][1] + 1<<'\n';
    }
    return;


    

}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}