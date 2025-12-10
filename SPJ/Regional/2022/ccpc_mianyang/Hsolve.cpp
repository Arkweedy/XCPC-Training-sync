#include<bits/stdc++.h>
using ll = long long;
using namespace std;

constexpr int N = 1e5;

void solve()
{
    int n;
    cin>>n;
    if(n <= 3){
        if(n == 1){
            cout<<"1\n1 1\n";
        }
        else if(n == 2){
            cout<<"3\n100 100\n101 100\n102 99\n";
        }
        else{
            cout<<5<<"\n";
            cout<<"3 3\n";
            cout<<"3 4\n";
            cout<<"3 5\n";
            cout<<"3 6\n";
            cout<<"4 5\n";
        }
    }
    else{
        int r = n % 4;
        vector<int>x,y;
        if(r == 0){
            // 5 4
            // 5 5 
            // 6 4 
            // 6 5
            x = {5,5 ,6,6};
            y = {4, 5, 4,5};
        }
        else if(r == 1){
            x = {4,4,5,5};
            y = {5,6,5,6};
        }
        else if(r == 2){
            x = {5,5,6,6};
            y = {5,6,5,6};
        }
        else{
            x = {6,6,7,7};
            y = {4,5,4,5};
        }
        cout<<9<<endl;
        int d = n / 4 - 1;
        for(int i = 0;i < 4;i++){
            cout<<x[i] + d<<" "<<y[i] + d<<"\n";
        }
        cout<<1<<" "<<2<<"\n";
        cout<<2<<" "<<3<<"\n";
        cout<<3<<" "<<1<<"\n";
        cout<<3<<" "<<2<<"\n";
        cout<<3<<" "<<3<<"\n";
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while (tt--)
    {
        solve();
    }
    return 0;    
}
