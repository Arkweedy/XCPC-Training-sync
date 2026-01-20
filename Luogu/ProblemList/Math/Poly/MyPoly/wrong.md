```c++
using biPoly = vector<poly>;

biPoly biMul(const biPoly& A, const biPoly& B, int n, int m)//mod x^n, y^m
{
    int Ay = min<int>(A.size(), m);
    int By = min<int>(B.size(), m);
    int Cy = min<int>(Ay + By - 1, m);
    int Bsz = n * 2;//block size

    poly PA(Ay * Bsz), PB(By * Bsz);
    for(int i = 0;i < Ay;i++){
        for(int j = 0;j < A[i].size() && j < n;j++){
            PA[i * Bsz + j] = A[i][j];
        }
    }
    for(int i = 0;i < By;i++){
        for(int j = 0;j < B[i].size() && j < n;j++){
            PB[i * Bsz + j] = B[i][j];
        }
    }

    poly PC = PA * PB;
    biPoly C(Cy, poly(n));
    for(int i = 0;i < Ay;i++){
        for(int j = 0;j < n;j++){
            C[i][j] = PC[i * Bsz + j];
        }
    }
    return C;
}

biPoly neg_x(const biPoly& Q, int n){
    biPoly R = Q;
    for(auto& fx : R){
        if((int)fx.size() < n) fx.resize(n);
        for(int i=1;i<n;i+=2){
            fx[i] = -fx[i];
            if(fx[i] < 0)fx[i] += P;
        }
    }
    return R;
}

biPoly even_x(const biPoly& Q, int n)
{
    biPoly R(Q.size(), poly(n / 2));
    for(int i = 0;i < Q.size();i++){
        for(int j = 0;j * 2 + n % 2 < n;j++){
            R[i][j] = Q[i][j * 2];
        }
    }
    return R;
}

biPoly expo_x(const biPoly& Q, int n)
{
    biPoly R(Q.size(), poly(n * 2 - 1));
    for(int i = 0;i < Q.size();i++){
        for(int j = 0;j < n;j++){
            R[i][j * 2] = Q[i][j];
        }
    }
    return R;
}

biPoly composition(poly& p, biPoly& q, int m, int d, int n)
//calc [y^0]P(y)/Q(x,y) mod x^m, return R(x,y)
//under Formula Laurant Series P,R begin at y^{1-n}
{
    //Bostan-Mori
    // m -> mod x^m   ,d -> y^(d + 1)
    cerr << "in" << endl;
    if(m == 1){
        poly r(q.size());
        for(int i = 0;i < q.size();i++){
            r[i] = q[i][0];
        }
        poly res = p * r.inv(q.size()).trunc(n);
        
    }
    biPoly nq = neg_x(q, m);
    //x -> x^2
    biPoly v = even_x(biMul(nq, q, m, d + 1), m);
    //x^2 -> x
    auto u = expo_x(composition(p, v, m / 2, d * 2, n), m / 2); //w(x, y^-1) 
    auto w = biMul(u, nq, m, d + 1); 
    biPoly res(d + 1);
    for(int i = 0;i <= d;i++){
        res[i] = w[i].trunc(n);
    }
    return res;
}

poly comp(poly f, poly g, int m)
{
    poly bP = f.rev();
    biPoly bQ(2);
    bQ[0] = poly{1};
    bQ[1] = -g;
    auto ans = composition(bP, bQ, m, 1, f.size());
    return ans[0];
}
```