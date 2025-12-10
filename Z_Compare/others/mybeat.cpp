#include<bits/stdc++.h>
using namespace std;
int main()
{
    int cnt = 0;
    cout<<"Begin Compile..."<<endl;
    system("g++ -std=c++23 -O2 mycode.cpp -o execute\\mycode.exe > nul 2>&1");
    system("g++ -std=c++23 -O2 std.cpp -o execute\\std.exe > nul 2>&1");
    system("g++ -std=c++23 -O2 make_data.cpp -o execute\\make_data.exe > nul 2>&1");
    cout<<"Compile Success!"<<endl;
    while (1) //一直循环，直到找到不一样的数据
    {
        cnt++;
        system("execute\\make_data.exe > io\\data.in");
        system("execute\\mycode.exe < io\\data.in > io\\mycode.out");
        system("execute\\std.exe < io\\data.in > io\\std.out");
        if (system("fc io\\mycode.out io\\std.out > nul")){ //当 fc 返回 1 时，说明这时数据不一样

            cout << "Test " << cnt << " \033[31mWA\033[0m" << endl;
            break;                          
        }//不一样就跳出循环
        else{
            cout << "Test " << cnt << " \033[32mAC\033[0m" << endl;
        }
    }
    return 0;
}
