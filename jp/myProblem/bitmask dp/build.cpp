#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


int main(int argc ,char*argv[])
{
    system("g++ makedata.cpp -o makedata.exe");
    system("g++ dp.cpp -o dp.exe");
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    for(int i = x;i <= y;i++){
        string in = "makedata.exe > data\\" + to_string(i) + ".in";
        string out = "dp.exe < data\\" + to_string(i) + ".in > data\\" + to_string(i) + ".out";
        cerr<<in<<endl;
        cerr<<out<<endl;
        system(in.c_str());
        system(out.c_str());
    }
    
    return 0;
}