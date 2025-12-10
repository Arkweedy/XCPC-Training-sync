#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class dsu_rollback
{
    int n;
    int n1;
    int n2;
    int bridge;
    vector<int>fa;
    vector<int>sz;
    stack<int>st1;
    stack<int>st2;
    stack<int>st;


    
    

public:
    dsu_rollback(int n1, int n2)
    {
        this->n = n1 + n2 + 1;
        this->bridge = n1 + n2;
        this->n1 = n1;
        this->n2 = n2;
        fa.resize(n1 + n2 + 1);
        sz.resize(n1 + n2 + 1);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    int find(int p)
    {
        return fa[p]== p ? p : find(fa[p]);
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            st.push(-1);
            return false;
        }
        else {
            if (sz[fu] < sz[fv]) {
                swap(fu, fv);
            }
            sz[fu] += sz[fv];
            fa[fv] = fu;
            if(fu == bridge || fv == bridge){
                st.push(fv);
            }
            else if(fu < n1 && fv < n1){
                st1.push(fv);
            }
            else{
                st2.push(fv);
            }
            return true;
        }
    }

    void roll_back()
    {
        int p = st.top();
        st.pop();
        if (p != -1) {
            sz[fa[p]] -= sz[p];
            fa[p] = p;
        }
        return;
    }

};

void solve()
{
    
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