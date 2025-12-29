#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.29 16:06:01

void solve()
{
    int n;
    cin >> n;
    int sum = 0;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i];
    }
    vector<int>b(n + 1);
    for(int i = 0;i < n;i++){
        b[i] = a[i];
    }
    set<vector<int>>st;
    st.insert(b);

    queue<vector<int>>q;
    q.push(b);
    auto move = [&](vector<int>b, int i)->vector<int>
    {
        if(b[i] == 0)return vector<int>(0);
        b[i]--;
        b[n]++;
        return b;
    };
    auto add = [&](vector<int>b, int i)->vector<int>
    {
        if(b[n] < n)return vector<int>(0);
        b[n] -= n;
        b[i] += n;
        return b;
    };

    auto print = [&](vector<int>b)->void
    {
        for(auto x : b){
            cerr << x << " ";
        }
        cerr << endl;
    };

    auto print2 = [&](vector<int>a, vector<int>b)->void
    {
        for(auto x : a){
            cerr << x << " ";
        }
        cerr << "-> ";
        for(auto x : b){
            cerr << x << " ";
        }
        cerr << endl;
    };

    auto check = [&](vector<int>b)->void
    {
        for(auto x : b){
            cerr << x << " ";
        }
        for(int i = 0;i < n;i++){
            if(b[i] >= n - b[n]){
                cerr << "ok" << endl;
                return;
            }
        }
        cerr << "ill" << endl;
        return;
    };

    while(!q.empty()){
        auto b = q.front();
        q.pop();
        for(int i = 0;i < n;i++){
            auto c = move(b, i);
            if(!c.empty()){
                if(!st.count(c)){
                    st.insert(c);
                    q.push(c);
                    print2(b, c);
                }
            }
        }
        for(int i = 0;i < n;i++){
            auto c = add(b, i);
            if(!c.empty()){
                if(!st.count(c)){
                    st.insert(c);
                    q.push(c);
                    print2(b, c);
                }
            }
        }
    }

    cerr << st.size() << endl;

    for(auto b : st){
        check(b);
    }

    cerr << "\n\n\n";

    

    auto dfs = [&](auto&&self, vector<int>b, int rem, int cur)->void
    {
        if(cur == n + 1){
            if(rem != 0)return;
            if(!st.count(b)){
                check(b);
            }
            else{
                st.erase(b);
            }
            return;
        }
        for(int i = 0;i <= rem;i++){
            auto c = b;
            c[cur] = i;
            self(self, c, rem - i, cur + 1);
        }
        return;
    };
    cerr << "\n\n\n";
    dfs(dfs, vector<int>(n + 1, 0), sum, 0);
    cerr << "\n\n\n";
    for(auto b : st){
        print(b);
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