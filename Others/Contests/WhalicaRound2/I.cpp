#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//I.cpp Create time : 2026.04.08 13:11

constexpr i64 MOD = 998244353;

void solve()
{
    i64 x;
    cin >> x;
    if(x == 0){
        cout << 0 << ' ' << 1 << '\n';
        return;
    }

    i64 pa = x, qa = 1;
    i64 pb = x - MOD, qb = 1;
    i64 best_p = pa, best_q = qa;
    i64 best_sum = pa + qa;

    while(true){
        i64 cur_sum = pa + qa;
        if(cur_sum < best_sum){
            best_sum = cur_sum;
            best_p = pa;
            best_q = qa;
        }

        if(pa == 1 && pb == -1){
            break;
        }

        if(pa <= -pb){
            // On this segment, q increases by qa and the signed residue increases by pa.
            // We can jump directly to the last still-negative state.
            i64 t = (-pb - 1) / pa;
            if(t == 0){
                t = 1;
            }
            pb += t * pa;
            qb += t * qa;
        }
        else{
            // Here p = q * x mod MOD decreases linearly, so only the endpoint can improve.
            i64 t = (pa - 1) / (-pb);
            if(t == 0){
                t = 1;
            }
            pa += t * pb;
            qa += t * qb;
        }
    }

    cout << best_p << ' ' << best_q << '\n';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
