#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <random>
using namespace std;


int main() {
    system("g++ -std=c++23 makedata.cpp -o makedata.exe");
    system("makedata.exe");
    return 0;
}