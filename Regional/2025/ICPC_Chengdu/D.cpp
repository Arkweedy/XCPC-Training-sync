#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    constexpr int N = 21;
    //state : a, b, n, cur, step (cur state)
    //ofstream ferr("D.log");
    using state = array<int,5>;
    map<state,string>mp;
    queue<state>q;
    state bg = {0,0,N,0,1};
    q.push(bg);
    mp[bg] = "";
    while(!q.empty()){
        auto [a, b, n, cur,step] = q.front();
        //ferr<<"in state "<<a<<" "<<b<<" "<<n<<" "<<cur<<" "<<step<<endl;
        string str = mp[q.front()];
        q.pop();
        if(n == 0)continue;
        if(n != 0){
            state nst = {a,b,n,cur^1,(n <= 6 ? 3 : 1)};
            if(!mp.count(nst)){
                mp[nst] = str + "/";
                q.push(nst);
            } 
        }
        if(step == 1){
            //->2
            state nst;
            if(cur == 0){
                nst = {a + 1, b, n - 1, cur, 2};
            }
            else{
                nst = {a, b + 1, n - 1, cur, 2};
            }
            if(!mp.count(nst)){
                mp[nst] = str + "1";
                q.push(nst);
            }
        }
        else if(step == 2){
            for(int i = 2;i <= 7;i++){
                state nst;
                if(cur == 0){
                    nst = {a + i, b, n, cur, (n == 6 ? 3 : 1)};
                }
                else{
                    nst = {a, b + i, n, cur, (n == 6 ? 3 : 1)};
                }
                if(!mp.count(nst)){
                    mp[nst] = str + char('0' + i);
                    q.push(nst);
                }
            }
        }
        else{//step == 3
            state nst;
            if(cur == 0){
                nst = {a + 8 - n, b,n - 1,cur, 3};
            }
            else{
                nst = {a,b + 8 - n,n - 1, cur, 3};
            }
            if(!mp.count(nst)){
                mp[nst] = str + char('0' + 8 - n);
                q.push(nst);
            }
        }
    }

    int n;
    cin>>n;
    for(int i = 0;i < n;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        int flg = 1;
        for(int j = 1;j <= 3;j++){
            state st = {a,b,c,d,j};
            if(mp.count(st)){
                cout<<mp[st]<<"\n";
                flg = 0;
                break;
            }
        }
        if(flg)cout<<"NA\n";
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