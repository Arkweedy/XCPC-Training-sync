#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;

void solve()
{
    int n;
    cin>>n;
    if(n == 0){
        cout<<"6\n1 6 3 2 5 4\n";
    }
    else if(n == 1){
        cout<<"6\n1 1 4 5 1 4\n";
    }
    else if(n == 2){
        cout<<"1\n1\n";
    }
    else{
        vector<int>x(30);
        for(int i = 1;i < 30;i++){
            x[i] = (1 << i) - 1;
        }
        vector<int>stage;
        n--;
        stage.push_back(1);
        n--;
        for(int i = 29;i >= 1;i--){
            while(n >= x[i]){
                n -= x[i];
                stage.push_back(i);
            }
        }
        vector<int>ans;
        ans.push_back(1);
        constexpr int inf = 114514;
        for(int i = 0;i < stage.size();i++){
            for(int j = 0;j < stage[i];j++){
                ans.push_back(inf - i);
            }
        }

        cout<<ans.size()<<endl;
        for(auto x : ans){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}