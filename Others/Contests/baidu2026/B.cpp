#include<bits/stdc++.h>

using i64 = long long;

using namespace std;

int lowbit(int x)
{
    return x & -x;
}

template<typename T>
struct Fenwick{
    int n;
    vector<T>a;

    Fenwick(int n_ = 0){init(n_);}

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T & v){
        for(int i = x + 1;i <= n;i += lowbit(i)){
            a[i - 1] = a[i - 1] + v;
        }
    }

    int select(const T& k) // <= k max x
    {
        int x = 0;
        T cur{};
        for(int i = 1 << __lg(n); i;i /= 2){
            if(x + i <= n && cur + a[x + i - 1] <= k){
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    auto b = a;
    sort(b.begin(), b.end());
    map<int, vector<int>>mp;
    map<int,int>cur;
    vector<int>pos(n);
    for(int i = 0;i < n;i++){
        mp[a[i]].push_back(i);
    }
    for(int i = 0;i < n;i++){
        pos[i] = mp[b[i]][cur[b[i]]];
        cur[b[i]]++;
    }

    // for(int i = 0;i < n;i++){
    //     cerr << pos[i] << " ";
    // }
    // cerr << endl;


    // segment insert/delete
    int sumlen = 0;
    int sumcnt = 0;
    Fenwick<int>t(n + 10);
    set<pair<int,int>>seg;

    int c = m + 1;

    auto addt = [&](int x)->void
    {
        //cerr << "add " << x << endl;
        if(sumcnt < c){
            t.add(x, 1);
            sumcnt++;
            sumlen += x;
        }
        else{
            int more = sumcnt - c;
            int old = t.select(more);
            if(x > old){
                sumlen += x - old;
            }
            t.add(x, 1);
        }
    };
    auto delt = [&](int x)->void
    {
        //cerr << "del " << x << endl;
        assert(sumcnt > 0);
        if(sumcnt <= c){
            t.add(x, -1);
            sumcnt--;
            sumlen -= x;
        }
        else{
            int more = sumcnt - c - 1;
            int old = t.select(more);
            if(x > old)sumlen -= x - old;
            t.add(x, -1);
            sumcnt--;
        }
    };

    auto add = [&](int p)->void
    {   
        //cerr << "ADD " << p << endl;
        int l = p, r = p;
        auto it = seg.lower_bound(make_pair(p,p));
        if(it != seg.begin()){
            auto pit = prev(it);
            auto [ll,lr] = *pit;
            if(lr + 1 == l){
                l = ll;
                seg.erase(pit);
                delt(lr - ll + 1);
            }
        }
        it = seg.lower_bound(make_pair(p,p));
        if(it != seg.end()){
            auto [rl,rr] = *it;
            if(rl == r + 1){
                r = rr;
                seg.erase(it);
                delt(rr - rl + 1);
            }
        }
        seg.insert(make_pair(l, r));
        addt(r - l + 1);
    };

    auto del = [&](int p)->void
    {
        //cerr << "DEL " << p << endl;
        int l = p, r = p;
        auto it = seg.lower_bound(make_pair(p, p));
        
        if(it != seg.end()){
            auto [pl, pr] = *it;
            if(pl == l){
                if(pr == r){
                    seg.erase(it);
                    delt(1);
                }
                else{
                    seg.erase(it);
                    delt(pr - pl + 1);
                    seg.insert(make_pair(l + 1, pr));
                    addt(pr - l);
                }
            }
            else{// prev
                auto pit = prev(it);
                auto [L, R] = *pit;
                if(R == r){ // [L, p - 1]
                    seg.erase(pit);
                    delt(R - L + 1);
                    seg.insert(make_pair(L, p - 1));
                    addt(p - L);
                }
                else{// [L, p - 1], [p + 1, R]
                    seg.erase(pit);
                    delt(R - L + 1);
                    seg.insert(make_pair(L, p - 1));
                    addt(p - L);
                    seg.insert(make_pair(p + 1, R));
                    addt(R - p);
                }
            }
        }
        else{// prev
            auto pit = prev(it);
            auto [L, R] = *pit;
            if(R == r){ // [L, p - 1]
                seg.erase(pit);
                delt(R - L + 1);
                seg.insert(make_pair(L, p - 1));
                addt(p - L);
            }
            else{// [L, p - 1], [p + 1, R]
                seg.erase(pit);
                delt(R - L + 1);
                seg.insert(make_pair(L, p - 1));
                addt(p - L);
                seg.insert(make_pair(p + 1, R));
                addt(R - p);
            }
        }
    };

    // compare len max_m+1 <-> k
    // len -> ok 

    constexpr int inf = 1e9 + 10;
    int p = -1;
    int ans = inf;
    for(int i = 0;i < n;i++){
        while(p + 1 < n && sumlen < k){
            add(pos[p + 1]);
            p++;
        }
        //cerr << "# " << i << " " << p << endl;
        //cerr << sumlen << " " << sumcnt << endl;
        if(sumlen < k)break;
        ans = min(ans, b[p] - b[i]);
        del(pos[i]);
    }
    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}