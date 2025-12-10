#include<bits/stdc++.h>

using namespace std;

int main(int argc ,char* argv[])
{
    string s = argv[1];
    string cpp = s + ".cpp";
    string exe = s + ".exe";
    string in = string(argv[2]) + ".in";
    string out = s + ".out";
    string compile = "g++ -std=c++20 -O2 " + cpp +" -o " + exe;
    string run = exe + " < " + in + " > " + out;
    system(compile.c_str());
    cout<<"Complie Success"<<endl;
    auto bg = chrono::steady_clock::now();
    system(run.c_str());
    auto ed = chrono::steady_clock::now();
    cout<<"use time "<<chrono::duration_cast<chrono::milliseconds>(ed-bg)<<endl; 
    return 0;
}