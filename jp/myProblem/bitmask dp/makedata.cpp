#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int main()
{ 
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    int n = 7, m = 7;
    cout<<n<<" "<<m<<endl;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cout<< (g() % 20 <= 14  ? 'P' : 'H');
        }
        cout<<endl;
    }

    return 0;
}