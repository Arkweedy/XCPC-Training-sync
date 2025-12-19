#include <bits/stdc++.h>
using namespace std;

struct SlopeTrick {
    long long min_f = 0;     // 当前函数的最小值
    long long addL = 0, addR = 0; // 两侧偏移（用于“扩展/滑动最小值”）

    priority_queue<long long> L; // 存 (x - addL)，表示左侧断点（最大堆）
    priority_queue<long long, vector<long long>, greater<long long>> R; // 存 (x - addR)，右侧断点（最小堆）

    void pushL(long long x) { L.push(x - addL); }
    void pushR(long long x) { R.push(x - addR); }

    long long topL() const { return L.top() + addL; }
    long long topR() const { return R.top() + addR; }

    long long popL() { long long v = L.top(); L.pop(); return v + addL; }
    long long popR() { long long v = R.top(); R.pop(); return v + addR; }

    // 对应 g(x) = min_{|x-y|<=d} f(y)
    void slide_min(long long d) {
        addL -= d;
        addR += d;
    }

    // f(x) += |x-a|
    void add_abs(long long a) {
        if (L.empty()) { // 初始 f(x)=0（全轴），第一次加绝对值
            pushL(a);
            pushR(a);
            return;
        }
        long long l = topL();
        long long r = topR();
        if (a < l) {
            min_f += (l - a);
            popL();
            pushL(a);
            pushL(a);
            pushR(l);
        } else if (a > r) {
            min_f += (a - r);
            popR();
            pushR(a);
            pushR(a);
            pushL(r);
        } else {
            pushL(a);
            pushR(a);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, X;
    cin >> n >> m >> X;
    vector<long long> a(m), d(m);
    for (int i = 0; i < (int)m; i++) cin >> a[i];
    for (int i = 0; i < (int)m; i++) cin >> d[i];

    SlopeTrick st;
    for (int i = 0; i < (int)m; i++) {
        st.slide_min(d[i]);
        st.add_abs(a[i]);
    }

    long long minCost = st.min_f;
    cout << (X - minCost) << "\n";
    return 0;
}
