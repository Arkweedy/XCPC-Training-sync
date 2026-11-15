 #include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
using T = long long ;
constexpr T eps =0;
using namespace std;
struct Point{
    T x,y;
    int id;
    bool operator==(const Point & a) const{
        return abs(x - a.x) <= eps && abs(y - a.y) <= eps;
    }
    bool operator<(const Point & a) const{
        if(abs(x - a.x) <= eps) return y < a.y - eps;
        return x < a.x - eps;
    }
    bool operator>(const Point & a) const{
        return !(*this< a || *this == a);
    }
    Point operator+(const Point & a) const{
        return {x + a.x,y + a.y};
    }
    Point operator-(const Point & a) const{
        return {x - a.x,y - a.y};
    }
    T operator*(const Point& a) const{
        return x * a.x + y * a.y;
    }
    T operator^(const Point& a) const{
        return x * a.y - y * a.x;
    }
    int toleft(const Point & a) const{
        const auto t = (*this) ^ a;
        return (t > eps) - (t < -eps);
    }
};
struct Segment{
    Point a,b;
    int is_on(const Point & p) const{
        if(p == a || p == b) return -1;
        return (p-a).toleft(p - b) == 0 && (p-a) * (p-b) < - eps;
    }
};
struct Polygon{
    vector<Point> p;

    

};
struct Convex : Polygon {

    array<int,3>  is_in(const Point & a) const {
        const auto & p = this->p;
    
        if(a == p[0]) return {0,0,0};

        if( (p[1] - p[0]).toleft(a - p[0]) == -1 ||
            (p.back() - p[0]).toleft(a - p[0]) == 1)
            return {0,0,0};


        const auto cmp = [&](const Point &u,const Point &v){
            return (u - p[0]).toleft(v - p[0]) == 1;
        };

        const size_t i = 
            lower_bound(p.begin() + 1,p.end(),a,cmp) - p.begin();
        if(i == 1) {
            return {0,0,0};

        }
        if(i == p.size() - 1 && Segment{p[0],p[i]}.is_on(a)) return {0,0,0};


        if(Segment{p[i-1],p[i]}.is_on(a)) return {0,0,0};


        int s=((p[i] - p[i-1]).toleft(a - p[i-1]) > 0);
        if(s==0) return {0,0,0};
        return {1,(int)i-1,(int)i};
    }    


};

    Convex convexhull(vector<Point> p){
        vector<Point> st;
        sort(p.begin(),p.end());
        const auto check =[](const vector<Point> &st,const Point &u){
            const auto back1=st.back(),back2=*prev(st.end(),2);
            return (back1-back2).toleft(u-back1)<=0;

        };
        for(const Point &u :p){
            while(st.size()>1&&check(st,u)) st.pop_back();
            st.push_back(u);
        }
        size_t k=st.size();
        p.pop_back();    
        reverse(p.begin(),p.end());
        for(const Point &u:p){
            while(st.size()>k&&check(st,u)) st.pop_back();
            st.push_back(u);
        }
        st.pop_back();
        Convex ans;
        ans.p=st;
        return ans;
    }

int check(vector<Point> v,Point u){
    for(int i=0;i<3;i++){
        int j=(i+1)%3;
        if(((v[j]-v[i]).toleft(u-v[i]))!=1) return 0;
    }
    return 1;
}
void print(vector<Point> v){
    cout<<v.size()<<'\n';
    for(auto p:v) cout<<p.id<<' ';
    cout<<'\n';
}
void solve()
{
    int n,q;
    cin>>n>>q;
    
    vector<Point> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i].x>>v[i].y;
        v[i].id=i+1;
        
    }
    auto cov=convexhull(v);
//    cout<<cov.p.size()<<endl;
int p=cov.p.size();
if(p<=2){

    for(int i=1;i<=q;i++){
        int x,y;cin>>x>>y;
        cout<<-1<<'\n';
    }

}
else if(p==3){
    auto pp=cov.p;

    for(int i=1;i<=q;i++){
        Point u;
        cin>>u.x>>u.y;
        if(check(pp,u)){
            print(pp);
        }
        else {
            cout<<-1<<'\n';
        }
    }
}
else if(p==4){
    auto pp=cov.p;

    vector<vector<Point> > need;
    for(int i=0;i<4;i++)
    {
        vector<Point> v;
        for(int j=0;j<4;j++){
            if(j==i) continue;
            v.push_back(pp[j]);
        }
        need.push_back(v);
    }

    for(int i=0;i<n;i++){
        if(need.size()>4) continue;
        if((pp[2]-pp[0]).toleft(v[i]-pp[0])==0) continue;
        if((pp[3]-pp[1]).toleft(v[i]-pp[1])==0) continue;
        for(int j=0;j<4;j++){
            int jj=(j+1)%4;
            vector<Point> vv;
            vv.push_back(v[i]);
            vv.push_back(pp[j]);
            vv.push_back(pp[jj]);
            need.push_back(vv);
        }
    }


    for(int i=1;i<=q;i++){
            Point u;cin>>u.x>>u.y;


            auto [ys,a,b]=cov.is_in(u);
            if(!ys){
                cout<<-1<<'\n';
                continue;
            }
            
            int yes=0;
            for(auto tri:need){
                if(check(tri,u)) {
                    print(tri);
                    yes=1;
                    break;
                }
            }
            if(yes==0){
                print(pp);
            }
        }

}
else {



    auto pp=cov.p;
    for(int i=1;i<=q;i++){
        Point u;cin>>u.x>>u.y;
        auto [ys,a,b]=cov.is_in(u);
        if(!ys){
                            cout<<-1<<'\n';continue;
        }

        vector<Point>  vv;


        if(a>1&&b+1<pp.size()){

            vv.push_back(pp[0]);
            for(int i=-2;i<=1;i++) vv.push_back(pp[b+i]);
        }
        else if(a==1){
            vv.push_back(pp[0]);
            for(int i=-1;i<=2;i++) vv.push_back(pp[b+i]);
        }
        else {
            vv.push_back(pp[0]);
            for(int i=-2;i<=1;i++) vv.push_back(pp[a+i]);
        }


        // cov t;
        // t.p=vv;
        // auto [yu,a,b]=

        int err=1;
        for(int i=0;i<32;i++){
            vector<Point> uu;
            for(int j=0;j<5;j++){
                if(i>>j&1) uu.push_back(vv[j]);
            }
            if(uu.size()!=3) continue;

            if(check(uu,u)){
                print(uu);
                err=0;
                break;
            }
        }

        assert(err==0);

    }
}

    
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}