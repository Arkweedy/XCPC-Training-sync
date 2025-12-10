#include<bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;

using namespace std;

void solve()
{
    int n = 16;
    vector<vector<int>>a(n,vector<int>(n));
    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            cin>>a[i][j];
            a[j][i] = (1 ^ a[i][j]);
        }
    }

    vector<int>win(n),fail(n);
    vector<vector<int>>wi(n);
    vector<array<int,3>>wei(n);//win , sum wi : win - fali, idx
    vector<int>rnk(n);
    vector<int>v00,v01,v10,v20,v11,v02,v21,v12,v22;//win fail
    vector<vector<int>>vs(n,vector<int>(n));
    for(int i = 0;i < 15;i++){
        v00.push_back(i);
    }

    auto ft = [&](int &x, int &y)->void
    {
        if(a[x][y] == 1)swap(x,y);
        vs[x][y] = vs[y][x] = 1;
        fail[x]++;
        win[y]++;
        wi[y].push_back(x);
        wi[x].push_back(y);
    };

    auto recalc = [&]()->void
    {
        for(int i = 0;i < n;i++){
            wei[i][0] = win[i];
            wei[i][2] = -i;
            int sum = 0;
            for(auto x : wi[i]){
                sum += win[x] - fail[x];
            }
            wei[i][1] = sum;
        }

        vector<int>id(n);
        iota(id.begin(),id.end(),0);
        sort(id.begin(),id.end(),[&](int i, int j)->bool
        {
            return wei[i] > wei[j];
        });
        for(int i = 0;i < n;i++){
            rnk[id[i]] = i;
        }
    };
    
    //round 1 1-8 vs 9-16

    for(int i = 0;i < 8;i++){
        int x = i, y = i + 8;
        ft(x,y);
        v01.push_back(x);
        v10.push_back(y);
    }

    recalc();
    
    //round 2
    sort(v01.begin(),v01.end(),[&](int i, int j)->bool
    {
        return rnk[i] < rnk[j];
    });
    sort(v10.begin(),v10.end(),[&](int i, int j)->bool
    {
        return rnk[i] < rnk[j];
    });
    for(int i = 0;i < 4;i++){
        int x = v01[i], y = v01[7 - i];
        ft(x,y);
        v11.push_back(y);
        v02.push_back(x);
        
    }
    for(int i = 0;i < 4;i++){
        int x = v10[i], y = v10[7 - i];
        ft(x,y);
        v20.push_back(y);
        v11.push_back(x);
    }
    
    recalc();
    //round 3
    sort(v02.begin(),v02.end(),[&](int i, int j)->bool
    {
        return rnk[i] < rnk[j];
    });
    sort(v11.begin(),v11.end(),[&](int i, int j)->bool
    {
        return rnk[i] < rnk[j];
    });
    sort(v20.begin(),v20.end(),[&](int i, int j)->bool
    {
        return rnk[i] < rnk[j];
    });

    for(int i = 0;i < 2;i++){
        int x = v02[i],y = v02[3 - i];
        ft(x,y);
        v12.push_back(y);
    }

    for(int i = 0;i < 2;i++){
        int x = v20[i],y = v20[3 - i];
        ft(x,y);
        v21.push_back(x);
    }

    vector<int>vs11(8);
    for(int i = 0;i < 4;i++){
        int x = 0;
        int y = 7;
        while(vs11[x])x++;
        while(vs11[y]||vs[v11[x]][v11[y]])y--;

        vs11[x] = vs11[y] = 1;

        x = v11[x], y = v11[y];

        ft(x,y);
        v12.push_back(x);
        v21.push_back(y);
    }
    recalc();
    //Round 4
    sort(v12.begin(),v12.end(),[&](int i, int j)->bool
    {
        return rnk[i] < rnk[j];
    });
    sort(v21.begin(),v21.end(),[&](int i, int j)->bool
    {
        return rnk[i] < rnk[j];
    });

    auto check = [&](vector<int>cp)
    {
        return !vs[cp[0]][cp[1]] && !vs[cp[2]][cp[3]] && !vs[cp[4]][cp[5]];
    };

    vector<vector<int>>pri(16);
    pri[0] = {1,6,2,5,3,4};
    pri[1] = {1,6,2,4,3,5};
    pri[2] = {1,5,2,6,3,4};
    pri[3] = {1,5,2,4,3,6};
    pri[4] = {1,4,2,6,3,5};
    pri[5] = {1,4,2,5,3,6};
    pri[6] = {1,6,2,3,4,5};
    pri[7] = {1,5,2,3,4,6};
    pri[8] = {1,3,2,6,4,5};
    pri[9] = {1,3,2,5,4,6};
    pri[10] = {1,4,2,3,5,6};
    pri[11] = {1,3,2,4,5,6};
    pri[12] = {1,2,3,6,4,5};
    pri[13] = {1,2,3,5,4,6};
    pri[14] = {1,2,3,4,5,6};

    int tot = 0;
    for(auto p : pri){
        vector<int>cp(6);
        for(int i =0;i < 6;i++){
            cp[i] = v12[p[i] - 1];
        }
        if(check(cp)){
            for(int i = 0;i < 6;i+=2){
                int x = cp[i], y = cp[i + 1];
                ft(x,y);
                v22.push_back(y);
            }
            break;
        }
    }

    for(auto p : pri){
        vector<int>cp(6);
        for(int i =0;i < 6;i++){
            cp[i] = v21[p[i] - 1];
        }
        if(check(cp)){
            for(int i = 0;i < 6;i+=2){
                int x = cp[i], y = cp[i + 1];
                ft(x,y);
                v22.push_back(x);
            }
            break;
        }
    }
    
    recalc();
    //round 5

    sort(v22.begin(),v22.end(),[&](int i, int j)->bool
    {
        return rnk[i] < rnk[j];
    });
    for(auto p : pri){
        vector<int>cp(6);
        for(int i =0;i < 6;i++){
            cp[i] = v22[p[i] - 1];
        }
        if(check(cp)){
            for(int i = 0;i < 6;i+=2){
                int x = cp[i], y = cp[i + 1];
                ft(x,y);
            }
            break;
        }
    }
    
    for(int i = 0;i <= 15;i++){
        cout<<win[i]<<" "<<fail[i]<<endl;
    }

    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}