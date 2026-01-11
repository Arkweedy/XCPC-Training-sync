#include <bits/stdc++.h>
using namespace std;

struct GaussResult {
    // 0 = 无解, 1 = 唯一解, 2 = 多解
    int status;
    vector<double> x; // 若有解，返回一个解（多解时为一组特解）
};

static inline int sgn(double v, double eps) {
    if (fabs(v) < eps) return 0;
    return v > 0 ? 1 : -1;
}

// 解 n 元线性方程组：增广矩阵 a 为 n 行 (n+1) 列
GaussResult gauss_solve(vector<vector<double>> a, double eps = 1e-7) {
    int n = (int)a.size();
    int m = n + 1; // 增广
    vector<int> where(n, -1); // where[col] = row

    int row = 0;
    for (int col = 0; col < n && row < n; col++) {
        // 选主元：在 [row..n-1] 中找 |a[i][col]| 最大的行
        int sel = row;
        for (int i = row; i < n; i++) {
            if (fabs(a[i][col]) > fabs(a[sel][col])) sel = i;
        }
        if (fabs(a[sel][col]) < eps) continue; // 该列全是 0，跳过（自由变量）

        swap(a[sel], a[row]);
        where[col] = row;

        // 归一化主元行
        double div = a[row][col];
        for (int j = col; j < m; j++) a[row][j] /= div;

        // 消去其他行（得到行最简阶梯形更稳）
        for (int i = 0; i < n; i++) if (i != row) {
            double factor = a[i][col];
            if (fabs(factor) < eps) continue;
            for (int j = col; j < m; j++) {
                a[i][j] -= factor * a[row][j];
            }
        }
        row++;
    }

    // 判无解：0 ... 0 | b (b != 0)
    for (int i = 0; i < n; i++) {
        bool all0 = true;
        for (int j = 0; j < n; j++) {
            if (fabs(a[i][j]) >= eps) { all0 = false; break; }
        }
        if (all0 && fabs(a[i][n]) >= eps) {
            return {0, {}};
        }
    }

    // 构造一个解（自由变量取 0）
    vector<double> x(n, 0.0);
    for (int col = 0; col < n; col++) {
        if (where[col] != -1) {
            x[col] = a[where[col]][n]; // 因为主元行已归一化且其他列已消去
        }
    }

    // 判唯一/多解：是否存在自由变量
    for (int col = 0; col < n; col++) {
        if (where[col] == -1) {
            return {2, x}; // 多解
        }
    }
    return {1, x}; // 唯一解
}

// 示例 main：读入 n 和 n*(n+1) 的 double
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<double>> a(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            int x;
            cin >> x;
            a[i][j] = x;
        }
    }

    auto res = gauss_solve(a, 1e-7);

    cout.setf(std::ios::fixed);
    cout << setprecision(10);

    if (res.status == 0) {
        //cout << "No solution\n";
        cout << -1 << endl;
    } 
    else if (res.status == 2) {
        cout << 0 << endl;
        //cout << "Infinite solutions\n";
        // 如果你想输出一组特解：
        // for (int i = 0; i < n; i++) {
        //     cout << res.x[i] << (i + 1 == n ? '\n' : ' ');
        // }
    } 
    else {
        //cout << "Unique solution\n";
        // for (int i = 0; i < n; i++) {
        //     cout << res.x[i] << (i + 1 == n ? '\n' : ' ');
        // }
        for(int i = 0;i < n;i++){
            cout << "x" << i + 1 << "=" << res.x[i] << endl;
        }
    }
    return 0;
}
