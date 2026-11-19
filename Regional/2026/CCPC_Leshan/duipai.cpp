#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

int main()
{
    int t = 0;
    while(1){
        cout << "test " << t++ << endl;
        system("make.exe > H21.in");
        if(system("H2.exe < H21.in > H2.out 2> H2.err") != 0){
            cout << "WA" << endl;
            break;
        }
        else{
            cout << "AC" << endl;
        }
    }
    return 0;
}