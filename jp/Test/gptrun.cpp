// run.cpp
#include <bits/stdc++.h>
using namespace std;

int main(int c, char** v){
    string f=v[1], i=v[2], s=f+".cpp", o=f+".out", a=f+".ans";
    string cc = "g++ -std=g++20 -O2 \""+s+"\" -o \""+f+"\"";
    int cr = system(cc.c_str());
    if(cr){ cerr<<"CE\n"; return 2; }

// #ifdef _WIN32
//     string rc="\""+f+".exe\" < \""+i+"\" > \""+o+"\"";
// #else
//     string rc="./"+f+" < \""+i+"\" > \""+o+"\"";
// #endif

    auto t0=chrono::steady_clock::now();
    int rr = system(rc.c_str());
    auto t1=chrono::steady_clock::now();
    if(rr){ cerr<<"RE\n"; return 3; }

    long long ms = chrono::duration_cast<chrono::milliseconds>(t1-t0).count();
    cout << "ms " << ms << "\n";

    ifstream A(a);
    if(A.good()){
        ifstream X(o);
        string xa, xb; long long ln=1;
        bool ok=true;
        while(true){
            bool ga= (bool)getline(X, xa);
            bool gb= (bool)getline(A, xb);
            if(!ga || !gb){
                if(ga!=gb){ cout<<"wa ln "<<ln<<" (eof)\n"; ok=false; }
                break;
            }
            if(xa!=xb){
                size_t j=0, m=min(xa.size(), xb.size());
                while(j<m && xa[j]==xb[j]) ++j;
                cout<<"wa ln "<<ln<<" col "<<(j+1)<<"\n";
                ok=false; break;
            }
            ++ln;
        }
        if(ok) cout<<"ok\n";
    }
    return 0;
}
