#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int t = 10000;
    const int k = 5;
    const int n_each = 10;            // 10 * 10000 = 1e5
    const int BIG = 1000000000;

    cout << t << "\n";
    for (int tc = 0; tc < t; ++tc) {
        cout << n_each << " " << k << "\n";
        // 每组放 5 张 a<=b + 5 张 b<=a
        for (int i = 0; i < n_each; ++i) {
            int small = ((tc + i) % 100) + 1;  // 让小边在 [1,100] 内滚动
            int big   = BIG - ((tc + i) % 100);
            if (i < 5) {
                // a<=b
                cout << small << " " << big << "\n";
            } else {
                // b<=a
                cout << big << " " << small << "\n";
            }
        }
    }
    return 0;
}
