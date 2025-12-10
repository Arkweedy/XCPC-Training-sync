def power(a: int, b: int) -> int:
    """快速幂，等价于 C++ 里的模板 power"""
    res = 1
    while b:
        if b & 1:
            res *= a
        a *= a
        b //= 2
    return res


def solve():
    n = int(input().strip())

    # 预计算 f 和 g 数组，长度开到 21 就够了
    g = [0] * (n + 1)
    g[0] = 0
    g[1] = 1
    for i in range(2, n):
        if i % 2 == 0:
            g[i] = g[i - 1] + i // 2
        else:
            g[i] = g[i - 1] + i // 2 + 1
    N = n * (n + 1) // 2
    ans = 0
    ans += power(2, N)
    ans += 2 * power(2, (N + 2) // 3)
    ans += 3 * power(2, g[n])
    ans //= 6
    print(ans)


if __name__ == '__main__':
    tt = 1
    # tt = int(input().strip())
    for _ in range(tt):
        solve()