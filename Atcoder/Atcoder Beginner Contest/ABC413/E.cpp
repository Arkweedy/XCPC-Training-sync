#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin >> n;
    int len = 1 << n;
    vector<int>a(len);
    for(int i = 0;i < len;i++){
        cin>>a[i];
    }
    
    auto dc = [&](auto&&self, int l, int r, int isMin)->void
    {   
        if(l == r)return;
        int m = l + r - 1 >> 1;
        //cerr<<l<<" "<<r<<" "<<(isMin ? "min" : "max")<<endl;
        if(isMin){
            int lmi = *min_element(a.begin() + l, a.begin() + m + 1), rmi = *min_element(a.begin() + m + 1, a.begin() + r + 1);
            if(lmi < rmi){
                self(self,l,m,1);
                self(self,m+1,r,1);
            }
            else{
                self(self,l,m,0);
                self(self,m+1,r,0);
                reverse(a.begin() + l, a.begin() + r + 1);
            }
        }
        else{
            int lmi = *min_element(a.begin() + l, a.begin() + m + 1), rmi = *min_element(a.begin() + m + 1, a.begin() + r + 1);
            if(lmi > rmi){
                self(self,l,m,0);
                self(self,m+1,r,0);
            }
            else{
                self(self,l,m,1);
                self(self,m+1,r,1);
                reverse(a.begin() + l, a.begin() + r + 1);
            }
        }
        return;
    };
    dc(dc,0, len - 1,1);
    for(int i = 0;i < len;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
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