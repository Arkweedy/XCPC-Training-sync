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
    // for(int i = 0;i < n;i++){
    //     cin>>a[i];
    // }

    vector<array<int,3>>ans;

    auto shift = [&](int i)->bool
    {
        if(a[i] < a[i + 1]){
            swap(a[i], a[i + 1]);
            a[i] -= a[i + 1];
            return true;
        }
        else{
            return false;
        }
    };

    auto add = [&](int x, int y)->void
    {
        a[x] += a[y];
        ans.push_back({x,y,1});
        assert(a[x] <= n);
    };

    auto sub = [&](int x, int y)->int
    {
        if(a[x] > a[y]){
            a[x] -= a[y];
            ans.push_back({x,y,-1});
            return true;
        }
        else{
            return false;
        }
    };
    int k = log2(n) * 4;
    //k = 0;
    //cerr<<k * n<<endl;
    //k = sqrt(n);
    //k = sqrt(n) * 10;
    //k = 1;
    //k = 0;
    int x = 0;
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    for(int i = 0;i < n * k;i++){
        int p = g() % (n - 1);
        if(!sub(p,p + 1)){
            i--;
        }
        x++;
        // if(x == 100 * k){
        //     break;
        // }
    }
    

    int cnt = 0;
    ll sum = 0;
    for(int i = 1;i < n - 1;i++){
        sum += a[i];
        if(a[i] < a[i - 1] && a[i] < a[i + 1]){
            cnt++;
        }
    }

    int opcnt = 0;
    priority_queue<pair<int,int>>pq;//dec abs , l idx
    for(int i = 0;i < n - 1;i++){
        pq.push(make_pair(min(a[i],a[i + 1]), i));
    }
    vector<pair<int,int>>ans1;
    while(!pq.empty()){
        auto [d, pos] = pq.top();
        pq.pop();
        if(min(a[pos], a[pos + 1]) != d || a[pos] == a[pos + 1]) continue;
        int x = pos, y = pos + 1;
        if(a[x] < a[y])swap(x,y);
        sub(x,y);
        opcnt++;
        //update a
        if(x > 0 && a[x] != a[x - 1] )pq.push(make_pair(min(a[x] , a[x - 1]), x - 1));
        if(x < n - 1 && a[x] != a[x + 1])pq.push(make_pair(min(a[x] , a[x + 1]),x));
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