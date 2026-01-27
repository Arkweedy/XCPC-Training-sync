#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.24 14:22:49

using T = long double;
constexpr T eps = 1e-8;
constexpr T INF = numeric_limits<T>::max();
constexpr T PI = numbers::pi_v<T>;

struct Point{
    T x, y;
    bool operator==(const Point& a) const{
        return (abs(x - a.x) <= eps && abs(y - a.y) <= eps);
    }
    bool operator<(const Point& a)const{
        if(abs(x - a.x) <= eps)return y < a.y - eps;
        return x < a.x - eps;
    }

    Point operator+(const Point& a)const{return {x + a.x, y + a.y};}
    Point operator-(const Point& a)const{return {x - a.x, y - a.y};}
    Point operator*(const T& a)const{return {x * a, y * a};}
    Point operator/(const T& a)const{return {x / a, y / a};}
    T operator*(const Point& a)const{return x * a.x + y * a.y;}
    T operator^(const Point& a)const{return x * a.y - y * a.x;}

    T len2()const{return (x * x + y * y);}
    T dis2(const Point& a)const{
        return (a - (*this)).len2();
    }
    T dis(const Point&a )const{return sqrtl(dis2(a));}
    int quad()const{
        if(abs(x) <= eps && abs(y) <= eps)return 0;
        if(abs(y) <= eps)return x > eps ? 1 : 5;
        if(abs(x) <= eps)return y > eps ? 3 : 7;
        return y > eps ? (x > eps ? 2 : 4) : (x > eps ? 8 : 6);
    }

    Point rot(const T rad)const{
        return {x * cosl(rad) - y * sinl(rad), x * sinl(rad) + y * cosl(rad)};
    }

    Point rot(const T& cosr, const T& sinr){
        return {x * cosr - y * sinr, x * sinr + y * cosr};
    }
};

bool operator < (const Point& a, const Point& b){
    const int qa = a.quad(), qb = b.quad();
    if(qa != qb)return qa < qb;
    const auto t = a ^ b;
    return t > eps;
}

struct Circle{
    Point c;
    T r;

    bool operator==(const Circle& a)const{
        return c == a.c && abs(r - a.r) <= eps;
    }

    int is_in(const Point& p)const{
        const T d = p.dis(c);
        return abs(d - r) <= eps ? -1 : d < r - eps;
    }

    int relation(const Circle& a)const{
        if(*this == a)return -1;
        const T d = c.dis(a.c);
        if(d > r + a.r + eps)return 0;
        if(abs(d - r - a.r) <=eps)return 1;
        if(abs(d - abs(r - a.r)) <= eps)return 3;
        if(d < abs(r - a.r) - eps)return 4;
        return 2;
    }

    vector<Point>inter(const Circle&a)const{
        const T d = c.dis(a.c);
        const int t = relation(a);
        if(t == -1 || t == 0 || t == 4)return vector<Point>();
        Point e = a.c - c;
        e = e / sqrtl(e.len2()) * r;
        
        const T costh = (r * r + d * d - a.r * a.r) / (2 * r * d),
                sinth = sqrtl(1 - costh * costh);
        return vector<Point>{c + e.rot(costh, -sinth), c + e.rot(costh, sinth)};
    }
};


int n, nn;
int ans[1000];
void print()
{
    cout<<"NO\n";
    for(int i=0;i<n;i++) cout<<ans[i]<<' ';
    cout<<'\n';
}
vector<int> ve;
int vis[1<<21];
vector<Circle>c;

void deal(Point a)
{
    int p=0;
    vector<pair<Point,int>> v;
    
    for(int i=0;i<nn;i++)
    {
        int g=c[i].is_in(a);
        if(g==1) p^=1<<i;
        else if(g==-1)
        {
            Point b=a-c[i].c;
            b=b.rot(PI/2);
            v.push_back({b,i});
        }
    }
    int m=v.size();
    for(int i=0;i<m;i++) {
        auto [c,id]=v[i];
        v.push_back({Point{-c.x,-c.y},id});
        
    }
    sort(v.begin(),v.end(), [&](pair<Point, int>a, pair<Point, int>b)->bool
    {
        return a.first < b.first;
    }); 
    Point s={1,0};
    for(auto [c,id]:v){
        Point cc = c;
        if((s^cc)<=0) p^=1<<id;
    }
    ve.push_back(p);vis[p]=1;
    for(auto [c,id]:v)
    {
        p^=1<<id;
        ve.push_back(p);vis[p]=1;
    }
}
void solve()
{
    
    cin >> n;
    c.clear();c.resize(n);
    for(int i=0;i<n;i++) ans[i]=0;
    for(int i = 0;i < n;i++){
        int x, y,r;
        cin >> x >> y >> r;
        c[i] = Circle{Point{x,y},r};
    }
    nn = min(n, 4);
    if(n == 1){
        cout << "YES" << "\n";
        return;
    }
    vector<Point>cr;
    for(int i = 0;i < nn;i++){
        for(int j = i + 1;j < nn;j++){
            int r = c[i].relation(c[j]);
            if(r == 0 || r == 1){
                ans[i] = ans[j] = 1;
                print();
                return;
            }
            else if(r != 2){
                int p = c[i].r < c[j].r ? i : j;
                ans[p] = 1;
                print();
                return;
            }
            else{
                auto v = c[i].inter(c[j]);
                for(auto p : v){
                    cr.push_back(p);
                }
            }
        }
    }
    int p=0;
    ve.clear();
    for(auto c:cr) deal(c);
    for(int i=1;i<(1<<nn);i++) 
        if(!vis[i]) {p=i;break;}
    for(auto p:ve) vis[p]=0;
    if(!p)
    {
        cout<<"YES\n";
        return ;
    }
    for(int i=0;i<nn;i++) ans[i]=(p>>i&1);
    print();

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