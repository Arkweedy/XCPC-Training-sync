#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.26 22:43

struct trie{
    struct Node{
        map<int,int>ne;
        int id = -1;
    };

    vector<Node>t;
    trie(int n):t(1){t.reserve(n);}

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    void insert(vector<int>&a, int id)
    {
        //cerr << "insert " << id << endl;
        a.push_back(0);
        int p = 0;
        int n = a.size();
        
        for(int i = 0;i < n;i++){
            //cerr << "add " << a[i] << endl;
            if(!t[p].ne.count(a[i])){
                t[p].ne[a[i]] = newNode();
                //cerr << "newNode" << endl;
                t[t[p].ne[a[i]]].id = id;
            }
            p = t[p].ne[a[i]];
        }
        a.pop_back();
        return;
    }

    int minpath()
    {
        int p = 0;
        while(!t[p].ne.empty()){
            p = (*t[p].ne.begin()).second;
        }
        //cerr << p << endl;
        return t[p].id;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>a(n);
    int sum = 0;
    for(int i = 0;i < n;i++){
        int k;
        cin >> k;
        sum += k;
        a[i].resize(k);
        for(int j = 0;j < k;j++){
            cin >> a[i][j];
        }
        reverse(a[i].begin(),a[i].end());
        vector<int>na;
        set<int>s;
        for(int j = 0;j < k;j++){
            if(!s.count(a[i][j]))na.push_back(a[i][j]);
            s.insert(a[i][j]);
        }
        a[i] = move(na);
    }
    //O(n^2)
    vector<int>ans;
    vector<int>exi(n, 1);
    for(int i = 0;i < n;i++){
        trie t(sum);
        for(int j = 0;j < n;j++){
            if(exi[j]){
                t.insert(a[j], j);
            }
        }
        int p = t.minpath();
        if(p == -1)break;
        set<int>ers;
        for(int j = 0;j < a[p].size();j++){
            ans.push_back(a[p][j]);
            ers.insert(a[p][j]);
        }
        exi[p] = 0;
        sum -= a[p].size();
        vector<vector<int>>na(n);
        for(int j = 0;j < n;j++){
            if(exi[j]){
                na.reserve(a[j].size());
                for(int k = 0;k < a[j].size();k++){
                    if(!ers.count(a[j][k]))na[j].push_back(a[j][k]);
                }
            }
        }
        a = move(na);
    }

    for(auto x : ans){
        cout << x << " ";
    }
    cout << "\n";
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