#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.11 10:51:21
constexpr int B = 30;
struct trie
{
    vector<array<int,2>>t;
    trie(){
        t.push_back({-1,-1});
    }

    int newNode()
    {
        t.push_back({-1,-1});
        return t.size() - 1;
    }

    void insert(int x)
    {
        int p = 0;
        for(int i = B;i >= 0;i--){
            int v = (x >> i) & 1;
            if(t[p][v] == -1){
                t[p][v] = newNode();
            }
            p = t[p][v];
        }
        return;
    }

    int minxor(int x)
    {
        int p = 0;
        int res = 0;
        for(int i = B;i >= 0;i--){
            int v = (x >> i) & 1;
            if(t[p][v] != -1){
                p = t[p][v];
            }
            else{
                p = t[p][v ^ 1];
                res += (1 << i);
            }
        }
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n * 2);
    constexpr int N = 1 << 30;
    for(int i = 0;i < n * 2;i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());

    auto dc = [&](auto&&self, vector<int>&v, int k)->int
    {
        if(v.empty())return 0;
        if(k == -1)return 0;
        vector<int>l,r;
        for(int i = 0;i < v.size();i++){
            if((v[i] >> k) & 1)r.push_back(v[i]);
            else l.push_back(v[i]);
        }
        if(l.size() % 2 == 0 && r.size() % 2 == 0){
            return max(self(self, l, k - 1), self(self, r, k - 1));
        }
        else{
            int res = 2e9;
            trie t;
            for(auto x : l){
                t.insert(x);
            }
            for(auto x : r){
                res = min(res, t.minxor(x));
            }
            return res;
        }
    };

    int res = dc(dc, a, B);
    cout << res << endl;
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