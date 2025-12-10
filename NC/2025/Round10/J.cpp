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
    if(n % 2 == 1){
        cout<<-1<<endl;
        return;
    }
    else{
        if(n == 4){
            cout<<"0 0 0"<<"\n";
            cout<<"1 0 0"<<"\n";
            cout<<"1 1 0"<<"\n";
            cout<<"0 1 0"<<"\n";
            cout<<1<<"\n";
        }
        else if(n == 6){
            cout<<"0 0 0"<<"\n";
            cout<<"1 0 0"<<"\n";
            cout<<"1 1 0"<<"\n";
            cout<<"1 1 1"<<"\n";
            cout<<"0 1 1"<<"\n";
            cout<<"0 1 0"<<"\n";
            cout<<2<<"\n";
        }
        else{
            vector<int>x(n),y(n),z(n);
            int len = n / 2;
            for(int i = 0;i < n / 2;i++){
                z[i] = 1;
            }
            for(int i = 0;i < n / 2;i++){
                x[i] = i / 2;
            }
            for(int i = 0;i < n / 2;i++){
                y[i] = (i + 1) / 2;
            }
            for(int i = n - 1;i >= n / 2;i--){
                z[i] = 0;
                x[i] = x[n - i - 1];
                y[i] = y[n - i - 1];
            }
            for(int i = 0;i < n;i++){
                cout<<x[i]<<" "<<y[i]<<" "<<z[i]<<"\n";
            }
            cout<<"inf\n";
        }
    }
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