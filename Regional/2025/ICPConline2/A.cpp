#include<bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
const ld PI=3.1415926535;
struct Point{
    ll x,y;
    
    ll operator ^(Point a){
        return x *a.y - y*a.x;
    }
    
    ll operator  * (Point a){
        return x *a.x + y*a.y;
    }
    
    int toleft(Point a){
        const auto t = (*this) ^ a;
        return (t > 0) - (t < 0);
    }
    
    Point operator - (Point a) {
        return {x-a.x,y-a.y};
    }
    
    ll len2(){
        return (*this) * (*this);
    }
    
    ll dis2(Point a){
        return (a-(*this)).len2();
    }
    
    ld dis(Point a){
        return sqrtl(dis2(a));
    }
    
    bool operator < (Point a)const {
        return x < a.x;
    }
};

struct Polygon{
    vector<Point>p;
    
    size_t nxt(size_t i){
        return i==p.size() - 1?0:i+1;
    }
    size_t pre(size_t i){
        return i==0?p.size() - 1:i-1;
    }
    
    ld area() {
        ld sum = 0;
        for(size_t i = 0;i<p.size();i++)sum += p[i] ^ p[nxt(i)];
        return sum / 2;
    }
    
    ld circ(){
        ld sum = 0;
        for(size_t i = 0;i<p.size();i++)sum += p[i].dis(p[nxt(i)]);
        return sum;
    }
};

Polygon build(vector<Point>p){
    vector<Point>st;

    sort(p.begin(),p.end());
    auto check = [](vector<Point>&st, Point&u){
        auto back1 = st.back(),back2 = *prev(st.end(),2);
        return (back1-back2).toleft(u-back1)<=0;
    };

    for(Point &u:p){
        while(st.size()>1 && check(st,u))st.pop_back();
        st.push_back(u);
    }
    
    int k = st.size();
    p.pop_back();
    reverse(p.begin(),p.end());
    for(Point &u:p){
        while(st.size() > k&&check(st,u))st.pop_back();
        st.push_back(u);
    }
    st.pop_back();
    Polygon res;
    
    res.p = st;
    return res;
}

void solve()
{
    ll n ,r1,r2;cin>>n>>r1>>r2;
    vector<Point>p;
    for(int i=0;i<n;i++){
        ll x,y;cin>>x>>y;
        p.push_back({x,y});
    }
    
    auto c = build(p);
    ld S = c.area(),C = c.circ();
    //cout<<S<<' '<<C;
    S+=C*r1+PI*r1*r1;
    
    ld ans=0;
    ans=PI*r2*(2*r1*r2+PI*r2*r2)+S*2*r2+C*PI*r2*r2/2;
    printf("%.10Lf\n",ans);
}


int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
