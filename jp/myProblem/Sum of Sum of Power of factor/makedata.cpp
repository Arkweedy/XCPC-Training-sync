#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <random>
#include <filesystem>
using namespace std;

// 生成随机整数 [l, r]
int rand_int(mt19937& rng, int l, int r) {
    uniform_int_distribution<int> dist(l, r);
    return dist(rng);
}

// 生成随机长整数 [l, r]
long long rand_ll(mt19937& rng, long long l, long long r) {
    uniform_int_distribution<long long> dist(l, r);
    return dist(rng);
}

int main() {
    // ================== 可配置参数 ==================
    int x = 17;                      // 起始文件编号
    int y = 17;                     // 结束文件编号
    int N_min = 10000000;                  // N最小值
    int N_max = 10000000;           // N最大值
    long long k_min = 900000000;            // k最小值
    long long k_max = 1000000000;   // k最大值
    // ==============================================
    
    // 初始化高质量随机数生成器
    random_device rd;
    mt19937 rng(rd());
    
    // 创建data目录
    filesystem::create_directory("data");
    
    cout << "Generating test data from " << x << " to " << y << ":\n";
    for (int file_id = x; file_id <= y; file_id++) {
        string filename = "data/" + to_string(file_id);
        ofstream fin(filename + ".in");
        
        // 生成单组测试数据
        int N = rand_int(rng, N_min, N_max);
        long long k = rand_ll(rng, k_min, k_max);
        
        // 写入输入文件
        fin << N << " " << k << "\n";
        fin.close();
        
        cout << "  " << file_id << ".in: N=" << N << ", k=" << k << "\n";
        
        // 调用 std.exe 生成输出文件
        string cmd = "std.exe < " + filename + ".in > " + filename + ".out";
        int ret = system(cmd.c_str());
        
        if (ret != 0) {
            cerr << "Error running std.exe for test case " << file_id << endl;
            return 1;
        }
    }
    
    cout << "\nSuccessfully generated " << (y - x + 1) 
         << " test cases in data/\n";
    return 0;
}