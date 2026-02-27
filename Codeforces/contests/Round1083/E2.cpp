#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;

// ---------- Suffix Array for integer array (doubling) ----------
struct SA {
    int n;
    vector<int> s;      // with sentinel 0 at end
    vector<int> sa, rk, height;

    // sparse table for RMQ on height
    vector<vector<int>> st;
    vector<int> lg2;

    SA(const vector<int>& a) { // a without sentinel
        s = a;
        s.push_back(0); // sentinel, must be smallest
        n = (int)s.size();

        build_sa();
        build_lcp();
        build_rmq();
    }

    void build_sa() {
        sa.resize(n);
        rk.resize(n);
        vector<int> tmp(n), cnt(max(256, n) + 1);

        // initial rank by value (already compressed, but we can do counting-ish via map)
        // We'll just sort indices by s[i] first.
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int i, int j){ return s[i] < s[j]; });

        rk[sa[0]] = 0;
        int classes = 1;
        for(int i = 1; i < n; i++){
            if(s[sa[i]] != s[sa[i-1]]) classes++;
            rk[sa[i]] = classes - 1;
        }

        for(int k = 1; k < n; k <<= 1){
            // sort by (rk[i], rk[i+k]) using radix sort
            // shift left by k
            for(int i = 0; i < n; i++){
                sa[i] = (sa[i] - k + n) % n;
            }

            // counting sort by first key rk
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for(int i = 0; i < n; i++) cnt[rk[sa[i]]]++;
            for(int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
            vector<int> sa2(n);
            for(int i = n - 1; i >= 0; i--){
                sa2[--cnt[rk[sa[i]]]] = sa[i];
            }
            sa.swap(sa2);

            tmp[sa[0]] = 0;
            int new_classes = 1;
            for(int i = 1; i < n; i++){
                int cur = sa[i], prev = sa[i-1];
                pair<int,int> now = {rk[cur], rk[(cur + k) % n]};
                pair<int,int> prv = {rk[prev], rk[(prev + k) % n]};
                if(now != prv) new_classes++;
                tmp[cur] = new_classes - 1;
            }
            rk.swap(tmp);
            classes = new_classes;
            if(classes == n) break;
        }
    }

    void build_lcp() {
        height.assign(n, 0);
        int k = 0;
        for(int i = 0; i < n; i++){
            int r = rk[i];
            if(r == 0){ k = 0; continue; }
            int j = sa[r - 1];
            while(i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            height[r] = k;
            if(k) k--;
        }
    }

    void build_rmq() {
        lg2.assign(n + 1, 0);
        for(int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;

        int K = lg2[n] + 1;
        st.assign(K, vector<int>(n));
        st[0] = height;
        for(int k = 1; k < K; k++){
            for(int i = 0; i + (1 << k) <= n; i++){
                st[k][i] = min(st[k-1][i], st[k-1][i + (1 << (k-1))]);
            }
        }
    }

    // LCP of suffixes starting at i and j in the ORIGINAL array (without sentinel index n-1? careful)
    int lcp(int i, int j) const {
        if(i == j) return n - i;
        int x = rk[i], y = rk[j];
        if(x > y) swap(x, y);
        // query min on height[x+1..y]
        int l = x + 1, r = y;
        int k = lg2[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];

        // coordinate compress to 1..m (keep 0 for sentinel)
        vector<int> b = a;
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end());
        for(int i = 0; i < n; i++){
            a[i] = int(lower_bound(b.begin(), b.end(), a[i]) - b.begin()) + 1;
        }

        SA sa(a); // builds on a + [0] sentinel

        vector<long long> dp(n + 1, 0);
        dp[0] = 1;

        for(int i = 0; i < n; i++){
            int lim = i;
            for(int j = i + 1; j <= n; j++){
                if(j > lim){
                    dp[j] += dp[i];
                    if(dp[j] >= MOD) dp[j] -= MOD;
                }
                if(j < n){
                    int l = sa.lcp(i, j);
                    lim = max(lim, j + l);
                    if(lim > n) lim = n;
                }
                if(lim >= n && j >= lim) break; // optional prune
            }
        }

        cout << dp[n] % MOD << "\n";
    }
    return 0;
}