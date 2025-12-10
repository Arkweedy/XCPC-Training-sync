#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int>p(n),d(n);
    for(int i = 0;i < n;i++){
        cin>>p[i];
    }
    for(int i = 0;i < n;i++){
        cin>>d[i];
    }
    int q;
    cin>>q;
    while(q--){
        int a;
        cin>>a;
        vector<int>vs(n * 2);
        int sta = 1;
        int time = 0;
        a--;
        time--;
        while(1){
            if(sta == 1){
                int x = upper_bound(p.begin(),p.end(),a) - p.begin();
                if(x == n){
                    cout<<"YES"<<endl;
                    break;
                }
                
                //vs
                ll dis = p[x] - a;
                time += dis;
                if(time % k == d[x]){
                    if(vs[x + n * sta]){
                        cout<<"NO"<<endl;
                        //cerr<<"Not at"<<x + n * sta<<endl;
                        break;
                    }
                    //cerr<<"vs "<<x + sta * n<<endl;
                    vs[x + sta * n] = true;
                    sta ^= 1;
                }
                a = p[x];
            }else{
                int x = lower_bound(p.begin(),p.end(),a) - p.begin() - 1;
                if(x == -1){
                    cout<<"YES"<<endl;
                    break;
                }
                ll dis = a - p[x];
                time += dis;
                //vs
                if(time % k == d[x]){
                    if(vs[x + n * sta]){
                        cout<<"NO"<<endl;
                        //cerr<<"Not at"<<x + n * sta<<endl;
                        break;
                    }
                    //cerr<<"vs "<<x + sta * n<<endl;
                    vs[x + sta * n] = true;
                    sta ^= 1;
                }
                a = p[x];
            }
        }
    }
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