#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;




void solve()
{
    constexpr int N  = 1e6;
    vector<int>ans(N, -1);
    vector<int>vs(N);
    ans[1] = 1;
    ans[0] = -1;
    vs[0] = 1;
    auto calc = [&](auto&&self, int x)->int
    {   
        if(x == -1)return 0;
        if(vs[x])return ans[x];
        else{
            vs[x] = true;
            int res = 1145141919;
            for(int i = 1;i * i <= x;i++){
                if(x % i == 0){
                    if(i != 1){
                        int res1 = self(self,i - 2),res2 = self(self,x / i);
                        if(res1 != -1 && res2 != -1)
                            res = min(res, res1 + res2);
                    }
                    int res3 = self(self,i),res4 = self(self,x / i - 2);
                    if(res3 != -1 && res4 != -1)
                        res = min(res, res3 + res4);
                }
            }
            ans[x] = res == 1145141919 ? -1 : res;
            return ans[x];
            
        }
    };

    int tt;
    cin>>tt;
    while(tt--){
        int n;
        cin>>n;
        cout<<calc(calc,n)<<endl;
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
    return 0;
}