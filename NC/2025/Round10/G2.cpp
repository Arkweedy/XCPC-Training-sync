#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int mod = 1e9, N = 1e5 + 10;

int n, m, q, a[N], b[N];

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
 
using u128 = unsigned __int128;
using i128 = __int128;

struct Barrett {
public:
    Barrett(u32 m_) : m(m_), im((u64)(-1) / m_ + 1) {}
 
    constexpr u32 mod() const {
        return m;
    }
 
    constexpr u32 mul(u32 a, u32 b) const {
        u64 z = a;
        z *= b;
         
        u64 x = u64((u128(z) * im) >> 64);
         
        u32 v = u32(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }

    constexpr u32 operator()(i64 z) const {
        u64 x = u64((u128(z) * im) >> 64);
         
        u32 v = u32(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }
 
private:
    u32 m;
    u64 im;
};

inline ll read() {
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

void write(ll x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
    return;
}

void solve() {
    n = read(), m = read(), q = read();
    Barrett mo(n);
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    ll ans = 0;
    while (q--) {
        ll x = read(), y = read(), z = read();
        x = 1 + mo(x + ans);
        y = 1 + (y + ans) % mod;
        z = 1 + mo(z + ans);

        /*
        a[x] -> y
        */
        int l1 = 0, r1 = n;
        while (l1 < r1) {
            int mid = l1 + r1 + 1 >> 1;
            if (b[mid] < a[x])
                l1 = mid;
            else
                r1 = mid - 1;
        }
        /*
        删除 l1 + 1 这个位置的数。
        */
        if (y < a[x]) {
            int l2 = 0, r2 = l1;
            while (l2 < r2) {
                int mid = l2 + r2 + 1 >> 1;
                if (b[mid] < y)
                    l2 = mid;
                else
                    r2 = mid - 1;
            }
            for (int i = l1; i > l2; i--) b[i + 1] = b[i];
            b[l2 + 1] = y;
        } else if (y > a[x]) {
            int l2 = l1 + 1, r2 = n;
            while (l2 < r2) {
                int mid = l2 + r2 + 1 >> 1;
                if (b[mid] < y)
                    l2 = mid;
                else
                    r2 = mid - 1;
            }
            /// cout << y << ' ' << l2 << "??\n";
            for (int i = l1 + 1; i < l2; i++) {
                b[i] = b[i + 1];
            }
            b[l2] = y;
        }

        a[x] = y;
        ans = 0;
        int i = z;
        while (i > 0) {
            ans += b[i];
            i -= m;
        }
        write(ans);
        putchar('\n');
        // for (int i = 1; i <= n; i++) cout << b[i] << " \n"[i == n];
    }
}

int main() {
    int t = 1;
    while (t--) solve();
    return 0;
}