#include <bits/stdc++.h>
using namespace std;
static const int MOD = 998244353;
inline int add(int a,int b){return (a+=b)>=MOD?a-MOD:a;}
inline int mul(int a,int b){return 1LL*a*b%MOD;}
inline int qpow(int a,int b){int r=1;for(;b;b>>=1,a=mul(a,a))if(b&1)r=mul(r,a);return r;}

vector<int> G[5005];
int n;
// dp[u][a][b] : a=0/1 表示 u 是否选，b=0/1 表示子树内是否已经“违规”
// 用 vector<int> 存大小为 k 的方案数
vector<int> dp[5005][2][2];
int sz[5005];

// 多项式乘法（朴素 O(|A|*|B|)）
vector<int> polymul(const vector<int>& A, const vector<int>& B){
    if(A.empty() || B.empty()) return {};
    vector<int> C(A.size()+B.size()-1,0);
    for(int i=0;i<A.size();i++)
        for(int j=0;j<B.size();j++)
            C[i+j] = add(C[i+j], mul(A[i],B[j]));
    return C;
}

void dfs(int u,int fa){
    sz[u]=1;
    // 初始化：只考虑 u 自己
    dp[u][0][0] = {0,1}; // size=1, 状态 a=0, b=0
    dp[u][1][0] = {0,0,1}; // size=1, 状态 a=1, b=0
    dp[u][0][1] = {}; // 目前不可能违规
    dp[u][1][1] = {};

    for(int v:G[u]) if(v!=fa){
        dfs(v,u);
        // 新建临时
        vector<int> tmp[2][2];
        for(int a=0;a<2;a++)
            for(int b=0;b<2;b++)
                tmp[a][b].assign(sz[u]+sz[v]+1, 0);

        // 合并 u 的旧状态 与 v 的状态
        for(int au=0;au<2;au++){
            for(int bu=0;bu<2;bu++){
                auto &U = dp[u][au][bu];
                if(U.empty()) continue;
                for(int av=0;av<2;av++){
                    for(int bv=0;bv<2;bv++){
                        auto &V = dp[v][av][bv];
                        if(V.empty()) continue;
                        // 新违规标志
                        int bad = bu | bv | (au==0 && av==0);
                        auto &T = tmp[au][bad];
                        // 卷积
                        for(int i=0;i<U.size();i++){
                            if(!U[i]) continue;
                            for(int j=0;j<V.size();j++){
                                T[i+j] = add(T[i+j], mul(U[i], V[j]));
                            }
                        }
                    }
                }
            }
        }
        // 收回 u
        sz[u] += sz[v];
        for(int a=0;a<2;a++)
            for(int b=0;b<2;b++){
                dp[u][a][b].swap(tmp[a][b]);
                // 把多余 0 截掉
                while(!dp[u][a][b].empty() && dp[u][a][b].back()==0)
                    dp[u][a][b].pop_back();
            }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,0);

    // 收集所有「已经违规」的状态
    vector<int> F(n+1,0);
    for(int a=0;a<2;a++)
        for(int b=0;b<2;b++){
            if(b==0) continue; // 只取违规的
            auto &V = dp[1][a][b];
            for(int k=0;k<V.size();k++)
                F[k] = add(F[k], V[k]);
        }

    // 计算期望
    int ans = 0;
    for(int k=0;k<n;k++){
        int cnt = F[k];
        if(!cnt) continue;
        int inv = qpow(n-k, MOD-2);
        int term = mul(cnt, mul(n, inv));
        ans = add(ans, term);
    }
    cout << ans << '\n';
    return 0;
}