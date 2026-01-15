```c++
using c64 = complex<double>;
constexpr c64 I = c64(0, 1);
constexpr double PI = numbers::pi; //c++20

void dft(vector<c64>&f, int inv)
{
    int n = f.size();
    int j = 0;
    for(int i = 1;i < n;i++){
        int k = n >> 1;
        for(;k & j;k >>= 1){
            j ^= k;
        }
        j ^= k;
        if(j < i){
            swap(f[i], f[j]);
        }
    }

    for(int len = 2;len <= n;len <<= 1){
        double ang = 2 * PI / len * inv;
        c64 wlen = c64(cos(ang), sin(ang));
        vector<c64>w(len / 2);
        w[0] = 1;
        for(int i = 1;i < len / 2;i++){
            w[i] = w[i - 1] * wlen;
        }
        for(int i = 0;i < n;i += len){
            for(int j = 0;j < len / 2;j++){
                c64 u = f[i + j], v = f[i + j + len / 2] * w[j];
                f[i + j] = u + v;
                f[i + j + len / 2] = u - v;
            }
        }
    }

    if(inv == 1){
        for(int i = 0;i < n;i++){
            f[i] /= n;
        }
    }
    return;
}

void fft(vector<c64>& f)
{
    int n = 1;
    while(n < f.size())n *= 2;
    f.resize(n);
    dft(f, -1);
    return;
}

void ifft(vector<c64>& f)
{
    int n = 1;
    while(n < f.size())n *= 2;
    f.resize(n);
    dft(f, 1);
    return;
}

vector<i64> operator*(vector<i64>& a, vector<i64>& b)
{
    int m = a.size() + b.size() - 1;
    int n = 1;
    while(n < m)n *= 2;
    vector<c64>f(n), g(n);
    for(int i = 0;i < a.size();i++){
        f[i] = a[i];
    }
    for(int i = 0;i < b.size();i++){
        g[i] = b[i];
    }
    fft(f);
    fft(g);
    for(int i = 0;i < n;i++){
        f[i] *= g[i];
    }
    ifft(f);
    vector<i64>res(m);
    for(int i = 0;i < m;i++){
        res[i] = llround(f[i].real());
    }
    return res;
}
```