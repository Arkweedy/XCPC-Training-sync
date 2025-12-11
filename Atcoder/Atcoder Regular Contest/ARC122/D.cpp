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

    auto dc = [&](auto&&self, int l, int r, int k)->int
    {
        if(l > r)return 0;
        if(k == -1)return 0;
        int m = l;
        for(int i = l;i <= r;i++){
            if((a[i] >> k) & 1)break;
            m = i;
        }
        if((m - l + 1) % 2 == 0 && (r - m) % 2 == 0){
            return max(self(self, l, m, k - 1), self(self,m + 1, r, k - 1));
        }
        else{
            int res = 2e9;
            trie t;
            for(int i = l;i <= m;i++){
                t.insert(a[i]);
            }
            for(int i = m + 1;i <= r;i++){
                res = min(res, t.minxor(a[i]));
            }
            return res;
        }
    };

    int res = dc(dc, 0, n * 2 - 1, B);
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