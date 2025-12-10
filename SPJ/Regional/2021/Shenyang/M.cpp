#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int P = 998244353;

struct SA{
    int n;
    vector<int>sa,rk,lc;

    SA(string s){
        n = s.size();
        sa.resize(n);
        lc.resize(n-1);

        rk.resize(n);

        iota(sa.begin(),sa.end(),0);
        sort(sa.begin(),sa.end(),[&](int a,int b){
            return s[a] < s[b];
        });

        rk[sa[0]] = 0;
        for(int i = 1;i<n;i++){
            rk[sa[i]] = rk[sa[i-1]] + (s[sa[i]] != s[sa[i-1]]);
        }

        int k = 1;
        vector<int>tmp,cnt(n);

        tmp.reserve(n);

        while(rk[sa[n-1]] < n-1){
            tmp.clear();
            for(int i=0;i<k;i++){
                tmp.push_back(n-k+i);
            }
            for(auto i:sa){
                if(i>=k){
                    tmp.push_back(i-k);
                }
            }
            fill(cnt.begin(),cnt.end(),0);

            for(int i=0;i<n;i++){
                cnt[rk[i]]++;
            }

            for(int i=1;i<n;i++){
                cnt[i] += cnt[i-1];
            }

            for(int i=n-1;i>=0;i--){
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            }

            swap(rk,tmp);

            rk[sa[0]] = 0;

            for(int i=1;i<n;i++){
                rk[sa[i]] = rk[sa[i-1]] + (tmp[sa[i-1]] < tmp[sa[i]] ||
                                            sa[i-1] + k == n || 
                                        tmp[sa[i-1]+k] < tmp[sa[i] + k]);
            }
            k*=2;
        }

        for(int i=0,j=0;i<n;i++){
            if(rk[i] == 0){
                j = 0;
            }else{
                for( j-= j>0;i+j<n && sa[rk[i] -1] + j<n && s[i+j] == s[sa[rk[i]-1]+ j];){
                    j++;
                }
                lc[rk[i]-1] = j;
            }
        }

        build();
    }

    vector<vector<int>>st;

    void build(){
        st.assign(20,vector<int>(n-1));
        for(int i=0;i<n-1;i++)st[0][i] = lc[i];
        for(int i=1;i<20;i++){
            for(int j=0;j+(1<<i)-1<n-1;j++){
                st[i][j] = min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
    }

    int rmq(int a,int b){
        int k = __lg(b-a+1);
        return min(st[k][a],st[k][b-(1<<k)+1]);
    }

    int lcp(int i,int j){
        assert(i!=j);
        if(i>j)swap(i,j);
        return rmq(i,j-1);
    }
};

#define lowbit(x) ((x)&(-x))
const int N = 1e6 + 10;

#define ln (p<<1)
#define rn (p<<1|1)

int mi[N<<2],n;
void modify(int p,int l,int r,int x,int t){
    if(l==r){
        mi[p] = t;
        return;
    }
    int mid = l+r>>1;
    if(x>mid)modify(rn,mid+1,r,x,t);
    else modify(ln,l,mid,x,t);
    mi[p] = min(mi[ln],mi[rn]);
}



void solve()
{
    string s;cin>>s;
    n = s.size();

    SA sa(s);
    set<int>ha;
    vector<int>e(n+1,-1);

    auto& rk = sa.rk;
    auto & pos = sa.sa;
    // for(int i=0;i<n;i++)cout<<pos[i]<<' ';
    // cout<<endl;
    // for(int i=0;i<n;i++)cout<<rk[i]<<' ';
    // cout<<endl;
    for(int i=0;i<n;i++)modify(1,0,n-1,i,n);
    for(int i=0;i<n;i++){
        // cerr<<i<<"#\n";
        // cerr<<rk[i]<<endl;
        while(!ha.empty() && (*ha.begin())  <= e[i]){
            int x = (*ha.begin());
            modify(1,0,n-1,x,n);
            ha.erase(ha.begin());
        }


        int x = rk[i];

        if(ha.empty()){
            ha.insert(x);
            modify(1,0,n-1,x,i);
        }else{
            int l = (*ha.begin()),r = (*ha.rbegin());

            if(x < l){
                int t = max(pos[x],pos[l]) + sa.lcp(x,l);
                if(t > i){
                    e[t] = max(e[t],x);
                    ha.insert(x);
                    modify(1,0,n-1,x,i);
                }
            }
            else if(x > r){
                int t = max(pos[x],pos[r]) + sa.lcp(x,r);
                
                if(t > i){
                    e[t] = max(e[t],r);
                    ha.insert(x);
                    modify(1,0,n-1,x,i);
                }else{
                    for(auto u:ha)modify(1,0,n-1,u,n);
                    ha.clear();
                    ha.insert(x);
                    modify(1,0,n-1,x,i);
                }
            }else{
                
                auto it = ha.upper_bound(x);
                r = (*it);
                int t = max(pos[x],pos[r]) + sa.lcp(x,r);
                e[t] = max(e[t],x);

                it = prev(it);
                l = (*it);
                t = max(pos[x],pos[l]) + sa.lcp(x,l);
                e[t] = max(e[t],l);

                ha.insert(x);
                modify(1,0,n-1,x,i);
            }
        }
        {
            // int l = (*ha.begin()),r = (*ha.rbegin());
            // cerr<<l<<' '<<r<<endl;
        }
        int l = n - (*ha.begin());

        // cout<<n-x<<' '<<i<<"#\n";
        // cout<<l<<"?\n";
        // for(int j=1;j<=n;j++)cout<<bit[j]<<" \n"[j==n];
        cout<< mi[1]+1 <<' '<<i+1<<'\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
}