#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n = 100;
    int m = 5;
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    while(1){
        vector<int>a(n);
        for(int i = 0;i < n;i++){
            a[i] = g() % 2;
        }
        set<int>s;
        while(s.size() < m){
            s.insert(g() % n);
        }
        for(auto x : s){
            a[x] = -1;
        }
        auto check = [&](vector<int>a)->int
        {
            int res = 0;
            for(int i = 0;i < n;i++){
                for(int j = i;j < n;j++){
                    int x = 0;
                    for(int k = i;k <= j;k++){
                        if(a[k] == 1)x--;
                        else x++;
                        if(x < 0)break;
                    }
                    
                    if(x==0)res++;
                }
            }
            return res;
        };

        vector<int>pos;
        for(auto x : s){
            pos.push_back(x);
        }
        int len = 1 << m;
        set<int>ress;
        for(int i = 0;i < len;i++){
            vector<int>b = a;
            for(int j = 0;j < m;j++){
                if(i >> j & 1)b[pos[j]] = 1;
                else b[pos[j]] = 0;
            }
            ress.insert(check(b));
        }
        if(ress.size() == len){
            cout<<"ok"<<endl;
            for(int i = 0;i < n;i++){
                cout<<a[i]<<" ";
            }
            cout<<endl;
            for(int i = 0;i < len;i++){
                vector<int>b = a;
                for(int j = 0;j < m;j++){
                    if(i >> j & 1)b[pos[j]] = 1;
                    else b[pos[j]] = 0;
                }
                cout<<i<<" "<<check(b)<<endl;
            }
            break;
        }
        else{
            cerr<<"try , but size = "<<ress.size()<<endl;
        }
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
    system("pause");
    return 0;
}