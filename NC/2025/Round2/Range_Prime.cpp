#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_SIEVE = 3000000;
const int M = 2000000; // 分块数组大小

int p[MAX_SIEVE + 5], vis[MAX_SIEVE + 5], cnt;
ll vg[M], fg[M]; // 块的值和计数数组
int idg1[M], idg2[M]; // 离散化映射数组

// 初始化素数表
void init_primes() {
    cnt = 0;
    for (int i = 2; i <= MAX_SIEVE; i++) {
        if (!vis[i])
            p[++cnt] = i;

        for (int j = 1; j <= cnt && i * p[j] <= MAX_SIEVE; j++) {
            vis[i * p[j]] = 1;

            if (i % p[j] == 0)
                break;
        }
    }
}

// 查询 1 到 n 的素数个数
ll get_pcnt(ll n) {
    if (n <= 1)
        return 0;

    ll sqrt_n = sqrt(n);
    int m = 0;

    // 分块
    for (ll l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        vg[++m] = n / l;

        if (n / l <= sqrt_n)
            idg1[n / l] = m;
        else
            idg2[n / (n / l)] = m;
    }

    // 初始化每个块的计数值
    for (int i = 1; i <= m; i++) {
        fg[i] = vg[i] - 1;
    }

    // 筛法处理
    for (int j = 1; j <= cnt && (ll)p[j] <= sqrt_n; j++) {
        for (int i = 1; i <= m && (ll)p[j] * p[j] <= vg[i]; i++) {
            ll t = vg[i] / p[j];
            int k;

            if (t <= sqrt_n)
                k = idg1[t];
            else
                k = idg2[n / t];

            fg[i] -= (fg[k] - (j - 1));
        }
    }

    return fg[1]; // 返回 n 对应的素数个数
}

int main() {
    init_primes(); // 初始化素数表
    int q;
    cin>>q;
    while(q--){
        ll n;
        cin >> n;
        cout << get_pcnt(n) << endl;
    }
    return 0;
}