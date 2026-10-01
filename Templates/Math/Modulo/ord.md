```c++
int power(int a, int p, int P)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

vector<int> factorize(int n) // or Miller-Rabin + Pollard Rho
{
    vector<int>res;
    for(int i = 2;i * i <= n;i++){
        while(n % i == 0){
            res.push_back(i);
            n /= i;
        }
    }
    if(n != 1)res.push_back(n);
    return res;
}

int phi(int n)
{
    auto facs = factorize(n);
    int phi = 1;
    for(int i = 0;i < facs.size();i++){
        if(i == 0 || facs[i] != facs[i - 1])phi *= (facs[i] - 1);
        else phi *= facs[i];
    }
    return phi;
}

int ord(int n, int k)
{
    k %= n;
    if(gcd(n, k) != 1)return 0;

    int s = phi(n);
    auto pfacs = factorize(s);
    for(auto q : pfacs){
        while(s % q == 0 && power(k, s / q, n) == 1){
            s /= q;
        }
    }

    return s;
}
```