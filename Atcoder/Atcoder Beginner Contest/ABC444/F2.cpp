#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.07 20:47

void solve()
{
    i64 n;
    cin >> n;
    i64 m;
    cin >> m;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    i64 h = (n + m) / 2;

    auto check = [&](i64 k)->bool
    {
        i64 opcnt = 0;
        i64 geq = 0;// [k, 2k - 2], 
        i64 leq = 0;// == 2k - 1
        i64 lsum = 0;
        map<i64,i64>mp;

        auto calc = [&](i64 x)->void
        {
            if(x < k){
                lsum += x - 1;
                return;
            }
            i64 a = x;
            i64 b = x;
            i64 ac = 1, bc = 0;
            //a <= b
            while(a >= k * 2 && b >= k * 2){
                i64 c = a / 2, d = (b + 1) / 2;
                i64 cc = 0, dc = 0;
                cc += ac;
                dc += bc;
                if((a + 1) / 2 == c)cc += ac;
                else dc += ac;
                if(b / 2 == c)cc += bc;
                else dc += bc;
                opcnt += ac + bc;
                a = c, b = d;
                ac = cc, bc = dc;
            }
            if(a == 2 * k - 1)leq += ac;
            else geq += ac;
            mp[a] += ac;
            

            if(b >= k * 2){
                assert(b == k * 2);
                opcnt += bc;
                geq += bc * 2;
                mp[k] += bc * 2;
            }
            else{
                if(b == 2 * k - 1)leq += bc;
                else geq += bc;
                mp[b] += bc;
            }

        };

        for(int i = 0;i < n;i++){
            calc(a[i]);
        }



        //1. leq -> les + eq
        //2. l -> 1
        //2. r -> l
        //3. eq -> l + l
        if(opcnt >= m){
            i64 more = opcnt - m;
            if(leq + geq - more > h)return 1;
            else return 0;
        }
        else{
            i64 ned = m - opcnt;
            if(leq >= ned){
                leq -= ned;
                geq += ned;
                opcnt += ned;
                lsum += (k - 2) * ned; 
                ned = 0;
            }
            else{
                ned -= leq;
                geq += leq;
                opcnt += leq;
                lsum += (k - 2) * leq; //point 1
                mp[2 * k - 1] = 0;// point 3
                leq = 0;
                
            }

            if(ned != 0){
                if(lsum >= ned){
                    //ok
                }
                else{
                    ned -= lsum; //point 2
                    for(auto rit = mp.rbegin(); rit != mp.rend();rit++){
                        auto [x, cnt] = *rit;
                        if((x - 1) * cnt >= ned){
                            i64 c = (ned + (x - 1) - 1) / (x - 1);
                            geq -= c;
                            break;
                        }
                        else{
                            geq -= cnt;
                            ned -= (x - 1) * cnt;
                        }
                    }
                    assert(ned > 0);
                }
            }
            if(leq + geq > h)return 1;
            else return 0;
        }
    };

    int l = 1, r = a.back() + 1;
    while(r - l > 1){
        int m = l + r >> 1;
        if(check(m)){
            l = m;
        }
        else{
            r = m;
        }
    }
    cout << l << endl;
    return;

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