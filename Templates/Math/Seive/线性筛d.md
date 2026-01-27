```c++
constexpr int N = 2000001;
vector<int>prime;
vector<int>lpfpow;
vector<int>d;
bitset<N + 1>isprime;
void seive()
{
    isprime.set();
    lpfpow.resize(N + 1);
    d.resize(N + 1);
    d[1] = 1;
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            d[i] = 2;
            lpfpow[i] = 1;
            prime.push_back(i);
        }
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)break;

            isprime.flip(i * p);
            if (i % p == 0) {  
                lpfpow[i * p] = lpfpow[i] + 1;
                d[i * p] = d[i] / (lpfpow[i] + 1) * (lpfpow[p * i] + 1);
                break;
            }
            else {
                lpfpow[i * p] = 1;
                d[i * p] = d[i] * 2;
            }
            
        }
    }
}
```