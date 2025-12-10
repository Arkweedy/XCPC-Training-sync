#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

// template<typename T>// T -> single add ^ , range_add 
// class cat_tree
// {
//     int n;
//     vector<T>a;
//     vector<vector<T>>pre,suf;

//     cat_tree(vector<T>&arr)
//     {
//         n = arr.size();
//         a = arr;
//         pre.resize(n * 4);
//         suf.resize(n * 4);
//         build(0,n - 1, 1);
//     }

//     void build(int l, int r, int p)
//     {
//         if(l == r){
//             tree[p] = a[l];
//         }
//         else{

//         }
//     };
// }

template<typename T,size_t M>
using matrixMaxPlus = array<array<T, M>, M>;

template<typename T,size_t M>
matrixMaxPlus<T,M> operator*(const matrixMaxPlus<T,M>& lhs, const matrixMaxPlus<T,M>& rhs)
{
    matrixMaxPlus<T,M>res{};
    for(int i = 0;i < M;i++){
        for(int j = 0;j < M;j++){
            for(int k = 0;k < M;k++){
                res[i][j] = max(res[i][j], lhs[i][k] + rhs[k][j]);
            }
        }
    }
    return res;
}

template<typename T,size_t M>
matrixMaxPlus<T,M>& operator+=(matrixMaxPlus<T,M>& lhs, array<T, 3>&rhs)//right plus
{
    const auto& [k, j, x] = rhs;
    for(int i = 0;i < M;i++){
        lhs[i][j] = max(lhs[i][j], lhs[i][k] + x);
    }
    return lhs;
}

template<typename T,size_t M>
matrixMaxPlus<T,M>& operator-=(matrixMaxPlus<T,M>& lhs, array<T, 3>&rhs)//left plus
{
    const auto& [i, k, x] = rhs;
    for(int j = 0;j < M;i++){
        lhs[i][j] = max(lhs[i][j], x + lhs[k][j]);
    }
    return lhs;
}

template<typename T,size_t M>
matrixMaxPlus<T,M>& operator+=(matrixMaxPlus<T,M>& lhs, vector<array<T, 3>>&rhs)//right plus
{
    auto res = lhs;
    for(const auto& [k, j, x] : rhs){
        for(int i = 0;i < M;i++){
            res[i][j] = max(lhs[i][j], lhs[i][k] + x);
        }
    }
    return res;
}

template<typename T,size_t M>
matrixMaxPlus<T,M>& operator-=(matrixMaxPlus<T,M>& lhs, vector<array<T, 3>>&rhs)//left plus
{
    auto res = lhs;
    for(const auto& [i, k, x] : rhs){
        for(int j = 0;j < M;i++){
            res[i][j] = max(lhs[i][j], x + lhs[k][j]);
        }
    }
    return res;
}





using matrix = matrixMaxPlus<ll,50>;

void solve()
{
    int n, m, q;
    cin>>n>>m>>q;
    vector<array<int,4>>e(m);
    for(int i = 0;i < n;i++){
        cin>>e[i][0]>>e[i][1]>>e[i][2]>>e[i][3];
    }
    sort(e.begin(),e.end(),[&](const array<int,4>&i, const array<int,4>&j)->bool
    {
        return i[3] < j[3];
    });
    vector<int>ew(m);
    for(int i = 0; i < n;i++){
        ew[i] = e[i][3];
    }
    vector<pair<int,int>>qry(q);
    for(int i = 0;i < n;i++){
        cin>>qry[i].first>>qry[i].second;
    }


    vector<int>ans(q);
    auto cdq = [&](auto&&self, int l, int r, vector<int>qid)->void
    {
        if(qid.empty()){
            return;
        }
        if(l == r){
            
        }
        int m = l + r >> 1;
        vector<int>lq,rq,mq;
        for(int i = 0;i < qry.size();i++){
            if(qry[qid[i]].second <= m){
                lq.push_back(qid[i]);
            }
            else if(qry[qid[i]].first > m){
                rq.push_back(qid[i]);
            }
            else{
                mq.push_back(qid[i]);
            }
        }
        self(self, l, m, move(lq));
        self(self, m + 1, r,move(rq));

        int lp = lower_bound(ew.begin(),ew.end(),l) - ew.begin();
        int mp = upper_bound(ew.begin(),ew.end(),m) - ew.begin() - 1;
        int rp = upper_bound(ew.begin(),ew.end(),r) - ew.begin() - 1;
        vector<matrix>pre(mp - lp + 1 + 1), suf(rp - mp + 1);
        for(int i = 1;i <= mp - lp + 1;i++){
            pre[i] = pre[i - 1];
            pre[i] += //
        }
        for(int i = 1;i <= rp - mp;i++){
            suf[i] = suf[i - 1];
            suf[i] += //
        }   

        for(int i = 0;i < mq.size();i++){
            auto [ql,qr] = qry[mq[i]];
            int kl = lower_bound(ew.begin(),ew.end(),ql) - ew.begin();
            int kr = upper_bound(ew.begin(),ew.end(),qr) - ew.begin() - 1;
            auto res = (pre[m - kl] * suf[kr - m - 1]);
            for(int x = 0;x < M;x++){
                for(int y = 0; y < M;y++){
                    ans[mq[i]] = max(ans[mq[i]], res[i][j]);
                }
            }
        }

    };
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