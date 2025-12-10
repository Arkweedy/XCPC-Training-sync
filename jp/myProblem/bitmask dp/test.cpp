#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int main()
{
    system("g++ -std=c++20 -O2 std.cpp -o std.exe");
    int x = 1;
    int y = 25;
    for(int i = x;i <= y;i++){
        clock_t bg,ed;
        string test = "std.exe < data\\" + to_string(i) + ".in > data\\" + to_string(i) + ".out";
        bg = clock();
        system(test.c_str());
        ed = clock();
        cerr<<"test case "<<i<<" use time "<<ed - bg <<endl;
    }
    return 0;
}