#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; 
    if (!(cin >> s)) return 0;
    const int n = (int)s.size();

    vector<int> keep;           // 稀疏候选起点（长度倍增）
    keep.reserve(25);           // 2^25 > 3e7，足够

    for (int i = 0; i < n; ++i) {
        // 1) 逆着 keep 做一次“最大后缀回溯”
        vector<int> v;
        v.reserve(keep.size() + 1);
        v.push_back(i); // 新的一块（单字符）

        for (int t = (int)keep.size() - 1; t >= 0; --t) {
            int a = keep[t];
            v.push_back(a);
            if (t == 0) continue; // 没有更左的边界可比

            int b = keep[t - 1];
            char x = s[i];
            char y = s[i - a + b]; // 周期对齐位

            if (x > y) break;      // 更大的末位，停止回溯
            if (x < y) v.pop_back(); // 更小的末位，丢掉 a
            // 相等：继续往更左看（两者都暂时保留）
        }
        reverse(v.begin(), v.end());

        // 2) 输出（v[0] 是最左的最优起点）
        cout << (v[0] + 1) << ' ' << (i + 1) << '\n';

        // 3) 稀疏化到倍增塔
        keep.clear();
        for (int a : v) {
            if (keep.empty() || (i - keep.back() + 1) >= 2 * (i - a + 1))
                keep.push_back(a);
        }
    }
    return 0;
}
