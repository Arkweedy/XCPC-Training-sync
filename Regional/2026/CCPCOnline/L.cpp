#include<bits/stdc++.h>


using i64 = long long;
using ll = long long;

using namespace std;
void output(__int128 x){
    if(x>9) output(x/10);
    cout<<(int)(x%10);
}
struct node{
    __int128 v,num;
};
bool operator <(node a,node b){
    return a.v<b.v;
}
void dealans(vector<node> ve){
    //for(auto [v,num]:ve) cerr<<(int)v<<' '<<(int)num<<endl;
    __int128 ans=0;
    multiset<node> s;
    for(auto [v,num]:ve) s.insert({v,num});

    while(s.size()&&s.begin()->num>1){
        auto a=*s.begin();s.erase(s.begin());
        if(a.num>1){
            ans+=a.v*(a.num/2*2);
            s.insert({a.v<<1,a.num>>1});

            if(a.num%2){
                s.insert(node{a.v ,(__int128) 1});
            }
            
        }
        else{
            auto b=*s.begin();s.erase(s.begin());

            ans+=a.v+b.v;
            b.num--;
            if(b.num){s.insert(b);}
            s.insert({a.v+b.v,(__int128)1});
        }
    }
//    cout<<(int)ans;
    output(ans);

}
void solve()
{
    i64 n;
    cin >> n;
    int m;
    cin >> m;

    vector<array<i64,3>>a;
    
    for(i64 l = 1, r = 0; l <= n;l = r + 1){
        r = n / (n / l);
        a.push_back({l, r, n / l});
    }

    map<i64, int>mp;
    for(int i = 0;i < m;i++){
        i64 l, r;
        cin >> l >> r;
        mp[l]++;
        mp[r + 1]--;
    }
 
    

    vector<array<i64, 3>>b;
    int c = 0;
    i64 p = 1;
    for(auto [x, cnt] : mp){
        
        if(p <= x - 1)b.push_back({p, x - 1, c});
        p = x;
        c += cnt;
    }
    b.push_back({p, n, c});

    

    // for(auto [x, y, z] : a){
    //     cerr << x << " " << y << " " << z << endl;
    // }

    vector<node>vec;
    int pa = 0, pb = 0;
    while(pa < a.size() && pb < b.size()){
        auto [x, y, c1] = a[pa];
        auto [s, t, c2] = b[pb];
        i64 L = max(x, s), R = min(y, t);
        vec.push_back({__int128_t(c1) * c2, R - L + 1});
        if(y == R)pa++;
        if(t == R)pb++;
    }

    dealans(vec);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}

