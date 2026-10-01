```c++
struct Comb {
    int n;
    std::vector<int> _fac;
    std::vector<int> _invfac;
    std::vector<int> _inv;
     
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
     
    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
         
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = 1ll * _fac[i - 1] * i % P;
        }
        _invfac[m] = power(_fac[m], P - 2);
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = 1ll * _invfac[i] * i % P;
            _inv[i] = 1ll * _invfac[i] * _fac[i - 1] % P;
        }
        n = m;
    }
     
    int fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    int invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    int inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    int binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return 1ll * fac(n) * invfac(m) % P * invfac(n - m) % P;
    }
} comb;
```