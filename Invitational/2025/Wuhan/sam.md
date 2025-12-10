```c++
struct SAM
{
    static constexpr int M = 26;//size 
    struct Node{
        int len;
        int link;
        array<int,M>nxt;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;
    vector<vector<int>>ot;
    vector<int>endpos_cnt;
    vector<ll>string_dif_cnt;
    vector<ll>string_all_cnt;
    int last = 1;

    SAM(){
        init();
    }

    SAM(string& s){
        init();
        build(s);
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[0].nxt.fill(1);
    }

    int newNode()
    {
        t.push_back(Node());
        return t.size() - 1;
    }

    static inline int num(int x)
    {
        return x - 'a';
    }

    void extend(int x)
    {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while(p != 0 && t[p].nxt[x] == 0){
            t[p].nxt[x] = cur;
            p = t[p].link;
        }
        int q = t[p].nxt[x];
        if(p == 0){
            t[cur].link = 1; 
        }
        else if(t[q].len == t[p].len + 1){
            t[cur].link = q;
        }
        else{
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone].nxt = t[q].nxt;
            t[clone].len = t[p].len + 1;
            t[cur].link = clone;
            t[q].link = clone;
            while(p != 0 && t[p].nxt[x] == q){
                t[p].nxt[x] = clone;
                p = t[p].link;
            }
        }
        last = cur;
        return;
    }

    void build(string& s)
    {
        for(auto &c : s){
            extend(num(c));
        }
        get_out_linktree();
    }

    inline int nxt(int p, int x)
    {
        return t[p].nxt[x];
    }

    void get_out_linktree()
    {
        ot.resize(t.size());
        for(int i = 2;i < t.size();i++){
            ot[t[i].link].push_back(i);
        }
    }

    void calc_endpos_cnt(string &s)
    {
        endpos_cnt.resize(t.size());
        int p = 1;
        for(auto c:s){
            p = t[p].nxt[num(c)];
            endpos_cnt[p]++;
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                endpos_cnt[p] += endpos_cnt[s];
            }
        };
        dfs(dfs,1);
        endpos_cnt[1] = 1;
    }

    void calc_dif_string_cnt()
    {
        string_dif_cnt.assign(t.size(),1);
        vector<int>outdeg(t.size());
        vector<vector<int>>ig(t.size());//inner dag
        queue<int>q;
        for(int i = 1;i <t.size();i++){
            outdeg[i] = M - count(t[i].nxt.begin(),t[i].nxt.end(),0);
            if(outdeg[i] == 0)q.push(i);
            for(int j = 0;j < M;j++){
                if(t[i].nxt[j] != 0){
                    ig[nxt(i,j)].push_back(i);
                }
            }
        }
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : ig[p]){
                string_dif_cnt[s] += string_dif_cnt[p];
                outdeg[s]--;
                if(outdeg[s] == 0)q.push(s);
            }
        }
        return;
    }

    void calc_all_string_cnt()
    {
        string_all_cnt.resize(endpos_cnt.size());
        for(int i = 0;i < t.size();i++){
            string_all_cnt[i] = endpos_cnt[i];
        }
        //transform(endpos_cnt.begin(),endpos_cnt.end(),string_all_cnt.begin(),std::_Identity<int>());
        vector<int>outdeg(t.size());
        vector<vector<int>>ig(t.size());//inner dag
        queue<int>q;
        for(int i = 1;i <t.size();i++){
            outdeg[i] = M - count(t[i].nxt.begin(),t[i].nxt.end(),0);
            if(outdeg[i] == 0)q.push(i);
            for(int j = 0;j < M;j++){
                if(t[i].nxt[j] != 0){
                    ig[nxt(i,j)].push_back(i);
                }
            }
        }
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : ig[p]){
                string_all_cnt[s] += string_all_cnt[p];
                outdeg[s]--;
                if(outdeg[s] == 0)q.push(s);
            }
        }
        return;
    }
};


