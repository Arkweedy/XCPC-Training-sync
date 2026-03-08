```c++
struct trie
{
    struct Node{
        array<int, 2>next;
        int cnt;
        Node():next{}, cnt(){};
    };
    vector<Node>t;
    int root = 0;
    int cnt = 0;
    static constexpr int K = 29;

    trie():t(1){};

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    void insert(int x)
    {
        cnt++;
        int p = root;
        for(int i = K;i >= 0;i--){
            int v = (x >> i & 1);
            if(t[p].next[v] == 0)t[p].next[v] = newNode();
            p = t[p].next[v];
            t[p].cnt++;
        }
        return;
    }

    void del(int x)
    {
        cnt--;
        int p = root;
        for(int i = K;i >= 0;i--){
            int v = (x >> i & 1);
            if(t[p].next[v] == 0)t[p].next[v] = newNode();
            p = t[p].next[v];
            t[p].cnt--;
        }
        return;
    }

    int minxor(int x)
    {
        if(cnt == 0)return INT_MAX;
        int p = root;
        int ans = 0;
        for(int i = K;i >= 0;i--){
            int v = (x >> i & 1);
            if(t[p].next[v] == 0 || t[t[p].next[v]].cnt == 0){
                p = t[p].next[v ^ 1];
                ans += (1 << i);
            }
            else p = t[p].next[v];
        }
        return ans;
    }
};
```