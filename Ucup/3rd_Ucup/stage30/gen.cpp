#include <bits/stdc++.h>
using namespace std;

int main() {
    const int n = 1;
    const int K = 20;          // 最大化矩阵维度
    const int a = 100000;      // 拼接次数拉满
    const int L = 100000;      // 初始模板长度拉满（sum |si| <= 1e5）

    ofstream out("data.in");
    out << n << ' ' << K << ' ' << a << '\n';

    // s1: 全 'O'，保证每步都是 F = F * A，迅速变稠密且一直密集
    out << string(L, 'O') << '\n';

    // 链式平方：s_{n+i} = s_{n+i-1} s_{n+i-1}
    // 法规要求：1 <= li, ri < n+i。取 li=ri=n+i-1 合法且最慢。
    for (int i = 1; i <= a; ++i) {
        int x = n + i - 1;
        out << x << ' ' << x << '\n';
    }
    out.close();
    return 0;
}

