#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e6 + 10;

struct Point {
    ll x,y;


    int quad()const{
        if(abs(x)  <= 0 && abs(y) <= 0)return 0;
        if(abs(y) <= 0 )return x > 0 ? 1 : 5;
        if(abs(x) <= 0)return y > 0 ? 3 : 7;
        return y > 0 ? (x > 0 ? 2 : 4) : (x > 0 ? 8 : 6);
    }

    ll operator ^ (const Point &a)const{
        return x * a.y - y * a.x;
    }



};

bool cmp(const Point &a,const Point &b){
    const int qa = a.quad() ,qb = b.quad();

    if(qa != qb)return qa < qb;
    const auto t = a ^ b;

    return t > 0;
}

bool check(const Point &a,const Point &b){
    return !cmp(a,b)  && !cmp(b,a);
}

void solve()
{
    int n;cin>>n;
    vector<Point>p(n);
    for(int i=0;i<n;i++){
        cin >> p[i].x >> p[i].y;
        //cout<<p[i].x<<' '<<p[i].y<<endl;
    }
    sort(p.begin(),p.end(),cmp);

    int res = n;
    for(int i=0;i<n;){
        int j = i;
        while(j < n && check(p[i],p[j]))j++;
        int l = j, r  =  i + n;
        while(l<r){
            int mid = l+r>>1;
            if((p[i]^p[mid%n]) < 0)r = mid;
            else l = mid + 1;
        }
        int len = l - i;
        //cout<<i<<' '<<l<<endl;
        res = min(res,min(len,n-len));
        i = j;
    }
    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}