// Code by Whalica
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

void solve() {
    i64 s, m;
    std::cin >> s >> m;

    if (m % 2 == 0 && s % 2 == 1) {
        std::cout << -1 << "\n";
        return;
    }

    auto len = [&](i64 x) -> int {
        int res = 0;
        while (x) {
            res++;
            x >>= 1;
        }
        return res;
    };

    int lens = len(s), lenm = len(m);
    int n = std::max(lens, lenm);
    std::vector<int> ds(n), dm(n);
    for (int i = 0; i < n; i++) {
        ds[i] = (s >> i & 1);
    }
    for (int i = 0; i < n; i++) {
        dm[i] = (m >> i & 1);
    }
    dm.push_back(0);

    std::vector<int> next(n + 1);
    next[n] = 1E9;
    for (int i = n; i >= 1; i--) {
        if (i < lenm && dm[i] == 1) {
            next[i - 1] = i;
        } else {
            next[i - 1] = next[i];
        }
    }

    auto check = [&](i64 x) -> bool {
        std::vector<i64> cnt(n);
        int pos = s % 2 == 1 ? 0 : next[0];
        for (int i = 0; i < lens; i++) {
            if (ds[i] == 1) {
                i64 ncnt = (1LL << (i - pos)); 
                while (pos <= i){
                    if (cnt[pos] + ncnt > x) {
                        ncnt -= (x - cnt[pos]);
                        ncnt = (ncnt + (1LL << (next[pos] - pos)) - 1) / (1LL << (next[pos] - pos));
                        pos = next[pos];
                    } else {
                        cnt[pos] += ncnt;
                        ncnt = 0;
                        break;
                    }
                }
                if(ncnt > 0)return false;
            }
        }

        return true;
    };    

    i64 l = 1, r = s + 10, ans = 0;
    while (l <= r) {
        i64 mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if(ans == 0)std::cout << -1 <<"\n";
    else std::cout << ans << "\n";
}

/*
最高位有 1 的情况下，低位 1 可以匹配 0/1，0 只能匹配 0

如果 m 是奇数，那么一定有元素 1，一定可以成功
否则不一定
*/

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}