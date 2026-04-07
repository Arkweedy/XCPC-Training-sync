#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;

static char buf[1 << 23];
static int bp, bl;
inline int gc() {
    if (bp == bl) { bl = fread(buf, 1, sizeof(buf), stdin); bp = 0; }
    return bp < bl ? (unsigned char)buf[bp++] : -1;
}
inline void ri(int &v) {
    int c = gc(), s = 1;
    while (c <= ' ') c = gc();
    if (c == '-') { s = -1; c = gc(); }
    v = 0;
    while (c >= '0' && c <= '9') { v = v * 10 + c - '0'; c = gc(); }
    v *= s;
}

const int N = 1500005;
struct P { int x, y; };
P a[N], t[N], s[N]; // a=points, t=merge temp, s=strip

inline long long d2(const P &u, const P &v) {
    long long dx = u.x - v.x, dy = u.y - v.y;
    return dx * dx + dy * dy;
}

long long rec(int l, int r) {
    int n = r - l;
    if (n <= 3) {
        long long res = 9000000000000000000LL;
        for (int i = l; i < r; i++)
            for (int j = i + 1; j < r; j++) {
                long long dd = d2(a[i], a[j]);
                if (dd < res) res = dd;
            }
        if (n == 2) { if (a[l].y > a[l+1].y) swap(a[l], a[l+1]); }
        else if (n == 3) {
            if (a[l].y > a[l+1].y) swap(a[l], a[l+1]);
            if (a[l+1].y > a[l+2].y) swap(a[l+1], a[l+2]);
            if (a[l].y > a[l+1].y) swap(a[l], a[l+1]);
        }
        return res;
    }

    int m = (l + r) >> 1;
    int mx = a[m].x;
    long long d = min(rec(l, m), rec(m, r));

    // merge by y
    int i = l, j = m, k = 0;
    while (i < m && j < r) {
        if (a[i].y <= a[j].y) t[k++] = a[i++]; else t[k++] = a[j++];
    }
    while (i < m) t[k++] = a[i++];
    while (j < r) t[k++] = a[j++];
    memcpy(a + l, t, n * sizeof(P));

    // strip (already y-sorted)
    int c = 0;
    for (int i = l; i < r; i++) {
        long long dx = (long long)a[i].x - mx;
        if (dx * dx < d) s[c++] = a[i];
    }
    for (int i = 0; i < c; i++) {
        for (int j = i + 1; j < c && j <= i + 7; j++) {
            long long dy = (long long)s[j].y - s[i].y;
            if (dy * dy >= d) break;
            long long dd = d2(s[i], s[j]);
            if (dd < d) d = dd;
        }
    }
    return d;
}

int main() {
    int n; ri(n);
    for (int i = 0; i < n; i++) { ri(a[i].x); ri(a[i].y); }
    sort(a, a + n, [](const P &u, const P &v) { return u.x < v.x || (u.x == v.x && u.y < v.y); });
    //printf("%.6f\n", sqrt((double)rec(0, n)));
    long long res = rec(0, n);
    printf("%lld\n", res);
    // const long double eps = 1e-6;
    // ldouble a = sqrt(double(res)), b = sqrtl(res);
    // assert(abs(a - b) < eps);
    return 0;
}