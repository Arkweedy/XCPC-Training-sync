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
    set<int>s;
    int flg = 1;
    for(int i = 0;i < n;i++){
        set<int>st;
        int a, b, c;
        cin>>a>>b>>c;

       
        if((c - b) % a== 0){
            st.insert(abs(c - b) / a);           
        }
       
        if((a - c) % b == 0){
            st.insert(abs(a - c) / b);
        }
        
        if((b - a) % c == 0){
            st.insert(abs(b - a) / c);
        }

        if(flg){
            s = st;
            flg = 0;
        }else{
            set<int>ns;
            for(auto x : st){
                if(s.count(x)){
                    ns.insert(x);
                }
            }
            s = ns;
        }   
    }
    if(s.size() != 1){
        if(s.size() == 0){
            assert(0);
        }else{
            ull x = 0;
            
            while(1){
                x+= 10;
                x*= 114514;
            }
        }
    }
    //assert(s.size() == 1);
    cout<<*s.begin()<<endl;
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