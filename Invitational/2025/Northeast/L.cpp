#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
int n,m;
struct node{
    int v,i,j,op;
    bool operator < (const node & W)const {
        if(W.v!=v)return v>W.v;
        else if(op!=W.op)return op>W.op;// 有好位置
        else return i*n+j < W.i*n+W.j;//字典序比较小
    }
};

// 行 [0,2*m)
// 列 [1,n]

const int N = 1e3 + 10,M=1e5+10;
set<node>s;
set<pair<int,int>>seg[N];

bool st[N][N];// 0 表示没有人，1表示有人
int x[M],y[M];
node get(int i,int l,int r){
    node res;
    if(l==1&&r==n){
        // 每个位置权重一样，找第一个好位置。
        res.v = r-l+1;
        res.i = i;
        res.j = 1;
        int j = i^1;
        if(seg[j].size()){
            auto [lt,rt] = (*seg[j].begin());
            res.j = lt;
        }
        res.op = st[i^1][res.j] ^1;
    }
    else if(l==1){
        res.v = r-l+1;
        res.i = i;
        res.j = 1;
        res.op =  st[i^1][1]^1;
    }
    else if(r==n){
        res.v = r-l+1;
        res.i = i;
        res.j = n;
        res.op =  st[i^1][n]^1;
    }
    else{
        res.v = (r-l+2)/2;
        node ans;
        ans.v = (r-l+2)/2;
        ans.i = i;
        res.i = i;
        ans.j = (l+r)/2;
        res.j = (l+r+1)/2;
        ans.op = st[i^1][ans.j] ^1;
        res.op = st[i^1][res.j] ^1;
        if(ans < res)res = ans;
    }
    return res;

}


// 表示增加空位，有人离开
void add(int i,int j){
    int lm = 0 ,rm = 0;
    if(j > 1 && !st[i][j-1])lm = 1;
    if(j < n && !st[i][j+1])rm = 1;

    int p = i^1;
    auto rt = seg[p].upper_bound({j,1e9});
    if(rt!=seg[p].begin()){
        rt = prev(rt);
        auto [l,r] = *rt;
        s.erase(get(p,l,r));
    }

    if(lm && rm){
        //合并两个
        auto rt = seg[i].upper_bound({j,1e9});
        int r = (*rt).second;
        auto lt = prev(rt);
        int l = (*lt).first;
                
        seg[i].erase({l,j-1});
        seg[i].erase({j+1,r});
        seg[i].insert({l,r});

        s.erase(get(i,l,j-1));
        s.erase(get(i,j+1,r));

        st[i][j] = 0;
        s.insert(get(i,l,r));
    }
    else if(lm){
        auto rt = seg[i].upper_bound({j,1e9});
        auto lt = prev(rt);
        int l = (*lt).first;
        seg[i].erase({l,j-1});
        seg[i].insert({l,j});

        s.erase(get(i,l,j-1));
        st[i][j] = 0;
        s.insert(get(i,l,j));
    }else if(rm){
        auto rt = seg[i].upper_bound({j,1e9});
        int r = (*rt).second;
        seg[i].erase({j+1,r});
        seg[i].insert({j,r});

        s.erase(get(i,j+1,r));
        st[i][j] = 0;
        s.insert(get(i,j,r));
    }
    else{
        seg[i].insert({j,j});
        st[i][j] = 0;
        s.insert(get(i,j,j));
    }

    // 注意处理对偶区间
    rt = seg[p].upper_bound({j,1e9});
    if(rt!=seg[p].begin()){
        rt = prev(rt);
        auto [l,r] = *rt;
        st[i][j] = 0;
        s.insert(get(p,l,r));
    }

    
    st[i][j] = 0;
}

// 空位置减少，表示有人进来 0 -> 1
void sub(int i,int j){
    if(i<0||j<=0)return;
    int lm = 0 ,rm = 0;
    if(j > 1 && !st[i][j-1])lm = 1;
    if(j < n && !st[i][j+1])rm = 1;

    int p = i^1;
    auto lt = seg[p].upper_bound({j,1e9});
    if(lt!=seg[p].begin()){
        lt = prev(lt);
        auto [l,r] = *lt;
        
        s.erase(get(p,l,r));
        // 把对面原始答案删去。
    }

    auto rt = seg[i].upper_bound({j,1e9});
    rt = prev(rt);
    auto [l,r] = *rt;
    s.erase(get(i,l,r));
    seg[i].erase({l,r});

    if(lm){
        seg[i].insert({l,j-1});
        s.insert(get(i,l,j-1));
    }
    if(rm){
        seg[i].insert({j+1,r});
        s.insert(get(i,j+1,r));
    }
    
    // 一切改好(seg)之后，重新计算
    lt = seg[p].upper_bound({j,1e9});
    if(lt!=seg[p].begin()){
        lt = prev(lt);
        auto [l,r] = *lt;
        st[i][j] = 1;
        s.insert(get(p,l,r));
    }

    st[i][j] = 1;


}

void solve()
{
    cin>>n>>m;
    m*=2;
    // m 行 n 列
    for(int i=0;i<m;i++){
        s.insert(get(i,1,n));
        seg[i].insert({1,n});
    }

    int q;cin>>q;
    while(q--){
        
        int op,t;cin>>op>>t;
        if(op==1){
            node res;
            res.v = -1,res.i = -2,res.j = -1;
            if(!s.empty()){
                res = (*s.begin());
            }
            x[t] = res.i,y[t] = res.j;
            cout<<res.i+1<<' '<<res.j<<'\n';
            sub(x[t],y[t]);
        }else{
            add(x[t],y[t]);
        }
    }


}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}