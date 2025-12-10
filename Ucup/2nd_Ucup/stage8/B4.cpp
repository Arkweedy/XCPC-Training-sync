#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 3e5 + 10;


void solve()
{
    int n,m;
    cin>>n>>m;
    multiset<int>a,b;
    vector<int>c(n);

    for(int i=0;i<n;i++){
        int x;cin>>x;
        a.insert(x);
        c[i] = x;
    }
    ll sum = 0;

    for(int i=0;i<m;i++){
        int x;cin>>x;
        b.insert(x);
        sum += x;
    }

    sort(c.begin(),c.end(),greater<int>());
    int L = c[m-1];
    map<int,int>ha;
    ll cur = 0;
    for(int i=0;i<m;i++)cur += c[i],ha[c[i]]++;

    auto add = [&](int x)->void{
        // x x + 1
        if(x<L)return;
        if(x==L){
            cur++;
            ha[x+1]++;
            ha[x]--;
            if(ha[x] == 0)L = x+1;
        }
    };
    vector<int>res;
    int i;
    for(i=0;i<n-m;i++){
        if(cur + n-m-i == sum)break;
        int x = (*a.begin());
        res.push_back(x);
        add(x);
        a.erase(a.begin());
        a.insert(x+1);
        a.erase(a.begin());
    }

    if(cur + n-m-i != sum){
        cout<<"-1\n";
        return;
    }

    int cnt = n - m - i;

    for(int i=0;i<m;i++){
        int y = (*b.rbegin());
        int x = (*a.rbegin());
        if(x>y){
            cout<<"-1\n";
            return;
        }
        while((*a.rbegin())!=(*b.rbegin())){
            res.push_back(*a.rbegin());
            a.erase(a.find(res.back()));
            a.insert(res.back()+1);
//            cerr<<res.back()<<' '<<(*a.begin())<<endl;
            a.erase(a.begin());
        }
        a.erase(a.find(*a.rbegin()));
        b.erase(b.find(*b.rbegin()));
    }

    cout<<res.size()<<'\n';
    for(auto k:res)cout<<k<<' ';
    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
