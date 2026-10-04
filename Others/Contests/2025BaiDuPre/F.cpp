#include<bits/stdc++.h>

using ll = long long;
using namespace std;

class trie
{
    struct Node
    {
        array<int,2>next;
        Node():next{}{}
    };

    vector<Node>t;

    trie()
    {
        init();
    }

    void init()
    {
        t.assign(2,Node());
        t[0].next.fill(1);
    }

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    void insert(int x)
    {
        int p = 1;
        for(int i = 20;i >= 0;i--){
            int q = (x >> i & 1) ? 1 : 0;
            if(t[p].next[q] == 0){
                t[p].next[q] = newNode();
            }
            p = t[p].next[q];
        }
        return;
    }

    int qry_min(int x)
    {
        int p = 0;
        
    }
    
};

constexpr int len = 20;

void solve()
{   
    array<int,1<<len>dis;
    dis.fill(21);
    int q, k;
    cin>>q>>k;
    while(q--){
        int op, x;
        cin>>op>>x;
        if(op == 1){//insert
            queue<int>q;
            q.push(x);
            dis[x] = 0;
            while(!q.empty()){
                int p = q.front();
                q.pop();
                //cerr<<"vs "<<p<<endl;
                for(int i = 0;i < len;i++){
                    int s = p ^ (1 << i);
                    if(dis[s] > dis[p] + 1){
                        dis[s] = dis[p] + 1;
                        q.push(s);
                    }
                }
            }
        }
        else{//qry
            cout<<dis[x]<<"\n";
        }
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
