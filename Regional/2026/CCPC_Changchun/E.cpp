#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

void solve()
{
    int n;
    vector<int>a(4);
    cin >> n >> a[1] >> a[2] >> a[3];
    vector<int>dis(4);

    vector<vector<int>>g(n + 1);
    auto addedge = [&](int i, int j)->void
    {
        g[i].push_back(j);
        g[j].push_back(i);
    };

    int p = 0;

    if(a[1] >= 2){
        addedge(1, 2);
        addedge(2, 3);
        a[1] -= 2;
        dis[1] = 3;
        dis[2] = 2;
        dis[3] = 1;
        p = 4;
    }
    else if(a[1] == 1){
        if(a[2] >= 1){
            addedge(1, 2);
            addedge(1, 3);
            dis[1] = 3;
            dis[2] = 1;
            dis[3] = 2;
            a[1]--;
            a[2]--;
            p = 4;
        }
        else if(a[2] == 0){//a3 >= 6
            addedge(1,4);
            addedge(1,6);
            addedge(3, 6);
            addedge(6, 5);
            addedge(5, 2);
            dis[1] = 6;
            dis[2] = 1;
            dis[3] = 4;
            a[1]--;
            a[3] -= 4;
            p = 7;
        }
    }
    else{
        if(a[3] == 0){
            cout << -1 << endl;
            return;
        }
        else if(a[2] >= 2){
            addedge(1,3);
            addedge(1, 4);
            addedge(2, 4);
            dis[1] = 4;
            dis[2] = 1;
            dis[3] = 3;
            a[2] -= 2;
            a[3] --;
            p = 5;
        }
        else if(a[2] == 1){
            addedge(1, 4);
            addedge(4, 8);
            addedge(6, 8);
            addedge(2, 8);
            addedge(6, 3);
            addedge(2, 5);
            addedge(2, 7);
            dis[1] = 8;
            dis[2] = 6;
            dis[3] = 3;
            a[2] --;
            a[3] -= 6;
            p = 9;
        }
        else if(a[2] == 0){
            addedge(1,4);
            addedge(1,6);
            addedge(1,8);
            addedge(4,7);
            addedge(8, 5);
            addedge(3, 8);
            addedge(2, 5);
            dis[1] = 8;
            dis[2] = 1;
            dis[3] = 4;
            a[3] -= 7;
            p = 9;
        }
    }

    while(a[1] > 0){
        addedge(p, dis[1]);
        dis[3] = dis[2];
        dis[2] = dis[1];
        dis[1] = p;

        a[1]--;
        p++;
    }

    while(a[2] > 0){
        addedge(p, dis[2]);
        dis[1] = p;

        a[2]--;
        p++;
    }

    while(a[3] > 0){
        addedge(p, dis[3]);

        dis[1] = p;
        swap(dis[2], dis[3]);

        a[3]--;
        p++;
    }

    for(int i = 1;i <= n;i++){
        for(auto j : g[i]){
            if(i < j){
                cout << i << " " << j << endl;
            }
        }
    }

    for(int i = 1;i <= n;i++){
        cout << i << " ";
    }
    cout << endl;

    return;
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}