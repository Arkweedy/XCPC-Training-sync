#include <bits/stdc++.h>
#include "genlib.hpp"
using namespace std;

// ==================== 配置区域 ====================

// 测试用例数量配置
int T_MIN = 1;          // 最少测试用例数
int T_MAX = 1;         // 最多测试用例数

// 字符串长度配置 (必须为偶数)
int N_MIN = 2;          // 最小长度
int N_MAX = 50;         // 最大长度 (对拍时建议用小数据)

// 字符集配置
// 0: 四种括号完全随机
// 1: 只生成圆括号 () 
// 2: 只生成方括号 []
// 3: 圆括号和方括号交替生成 (如 ()[]()[] )
// 4: 优先生成某种括号 (通过 BRACKET_BIAS 控制)
int CHAR_MODE = 0;      // 字符生成模式

// 当 CHAR_MODE = 4 时，控制括号偏好
// 0: 偏向圆括号, 1: 偏向方括号
int BRACKET_BIAS = 0;   // 括号偏好
double BIAS_RATIO = 0.7; // 偏好比例 (0.5~1.0)

// 正确序列配置
// 0: 完全随机生成
// 1: 生成已经是 beautiful 的字符串 (用于测试答案是否为0)
// 2: 生成接近 beautiful 的字符串 (少量错误)
// 3: 生成特定模式的字符串 (如全左括号或全右括号)
int GENERATION_MODE = 0;

// 当 GENERATION_MODE = 2 时，控制错误率
double ERROR_RATE = 0.2; // 错误字符比例 (0.0~1.0)

// 当 GENERATION_MODE = 3 时，控制特定模式
// 0: 全左括号 "(((...[[[..."
// 1: 全右括号 ")))...]]]..."
// 2: 左括号在前，右括号在后
// 3: 随机但保证某种括号序列已经合法
int SPECIAL_PATTERN = 0;

// 输出格式配置
bool PRINT_N = true;    // 是否输出 n (题目要求输出，建议保持true)

// 随机种子 (设为0使用当前时间)
unsigned long long FIXED_SEED = 0;

// ==================== 核心代码 ====================

mt19937_64 g;

// 生成 [l, r] 范围内的随机整数
int randint(int l, int r) {
    return uniform_int_distribution<int>(l, r)(g);
}

// 生成 [0, 1] 范围内的随机浮点数
double randdouble() {
    return uniform_real_distribution<double>(0, 1)(g);
}

// 生成单个字符
char gen_char() {
    const char brackets[] = {'(', ')', '[', ']'};
    
    switch (CHAR_MODE) {
        case 0: // 完全随机
            return brackets[randint(0, 3)];
            
        case 1: // 只生成圆括号
            return brackets[randint(0, 1)];
            
        case 2: // 只生成方括号
            return brackets[randint(2, 3)];
            
        case 3: { // 交替生成
            static int cnt = 0;
            return brackets[(cnt++ % 2) + (randint(0, 1) * 2)];
        }
            
        case 4: { // 偏向某种括号
            if (randdouble() < BIAS_RATIO) {
                // 生成偏好的括号类型
                return brackets[randint(BRACKET_BIAS * 2, BRACKET_BIAS * 2 + 1)];
            } else {
                // 生成另一种
                int other = 1 - BRACKET_BIAS;
                return brackets[randint(other * 2, other * 2 + 1)];
            }
        }
            
        default:
            return brackets[randint(0, 3)];
    }
}

// 生成正确的括号序列 (用于构造 beautiful 字符串)
string gen_correct_sequence(int n, char left, char right) {
    string res;
    res.reserve(n);
    int bal = 0;
    
    for (int i = 0; i < n; i++) {
        // 计算剩余位置
        int remain = n - i;
        
        // 如果剩余位置刚好等于需要的右括号数，只能放右括号
        if (remain == bal) {
            res += right;
            bal--;
        } 
        // 如果平衡度为0，只能放左括号
        else if (bal == 0) {
            res += left;
            bal++;
        }
        // 随机选择，但保证能完成
        else {
            if (randint(0, 1) == 0) {
                res += left;
                bal++;
            } else {
                res += right;
                bal--;
            }
        }
    }
    
    return res;
}

// 生成 beautiful 字符串
string gen_beautiful(int n) {
    // 决定圆括号和方括号的数量 (都必须是偶数)
    int round_cnt = randint(0, n / 2) * 2;  // 保证是偶数
    int square_cnt = n - round_cnt;          // 自动也是偶数
    
    string round_seq = gen_correct_sequence(round_cnt, '(', ')');
    string square_seq = gen_correct_sequence(square_cnt, '[', ']');
    
    // 交错合并两个序列
    string res;
    res.reserve(n);
    
    int i = 0, j = 0;
    while (i < round_cnt || j < square_cnt) {
        if (i < round_cnt && j < square_cnt) {
            // 随机选择从哪个序列取
            if (randint(0, 1) == 0) {
                res += round_seq[i++];
            } else {
                res += square_seq[j++];
            }
        } else if (i < round_cnt) {
            res += round_seq[i++];
        } else {
            res += square_seq[j++];
        }
    }
    
    return res;
}

// 生成接近 beautiful 的字符串 (带错误)
string gen_near_beautiful(int n) {
    string s = gen_beautiful(n);
    int errors = max(1, (int)(n * ERROR_RATE));
    
    for (int i = 0; i < errors; i++) {
        int pos = randint(0, n - 1);
        s[pos] = gen_char(); // 随机替换
    }
    
    return s;
}

// 生成特定模式的字符串
string gen_special(int n) {
    string res;
    res.reserve(n);
    
    switch (SPECIAL_PATTERN) {
        case 0: { // 全左括号
            int half = n / 2;
            for (int i = 0; i < half; i++) res += '(';
            for (int i = 0; i < half; i++) res += '[';
            break;
        }
            
        case 1: { // 全右括号
            int half = n / 2;
            for (int i = 0; i < half; i++) res += ')';
            for (int i = 0; i < half; i++) res += ']';
            break;
        }
            
        case 2: { // 左括号在前，右括号在后
            int half = n / 2;
            for (int i = 0; i < half; i++) {
                res += (randint(0, 1) == 0) ? '(' : '[';
            }
            for (int i = 0; i < half; i++) {
                res += (randint(0, 1) == 0) ? ')' : ']';
            }
            break;
        }
            
        case 3: { // 保证圆括号序列合法，方括号随机
            // 先生成合法的圆括号序列
            string round = gen_correct_sequence(n, '(', ')');
            // 随机替换一些为方括号
            res = round;
            int to_replace = randint(0, n);
            for (int i = 0; i < to_replace; i++) {
                int pos = randint(0, n - 1);
                res[pos] = (res[pos] == '(' || res[pos] == ')') ? 
                           (randint(0, 1) == 0 ? '[' : ']') : res[pos];
            }
            break;
        }
            
        default:
            return gen_beautiful(n);
    }
    
    return res;
}

// 生成单个测试用例
string gen_testcase(int n) {
    switch (GENERATION_MODE) {
        case 0: // 完全随机
            return string(n, ' '); // 占位，实际在下面填充
            
        case 1: // beautiful 字符串
            return gen_beautiful(n);
            
        case 2: // 接近 beautiful
            return gen_near_beautiful(n);
            
        case 3: // 特定模式
            return gen_special(n);
            
        default:
            return string(n, ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << 1 << endl;
    int n = 20;
    cout << n << endl;
    cout << gen::str::random_string(n, "[]()") << endl;
    
    // // 初始化随机数生成器
    // if (FIXED_SEED == 0) {
    //     g = mt19937_64(chrono::steady_clock::now().time_since_epoch().count());
    // } else {
    //     g = mt19937_64(FIXED_SEED);
    // }
    
    // // 生成测试用例数量
    // int t = randint(T_MIN, T_MAX);
    // cout << t << "\n";
    
    // // 确保总长度不超过题目限制 (2e5)
    // int total_n = 0;
    // const int MAX_TOTAL = 200000;
    
    // for (int tc = 0; tc < t; tc++) {
    //     // 动态调整 n 的范围，防止超出总限制
    //     int remaining = MAX_TOTAL - total_n;
    //     int max_n = min(N_MAX, remaining - (t - tc - 1) * N_MIN);
    //     max_n = max(max_n, N_MIN);
        
    //     // 保证是偶数
    //     int n = randint(N_MIN / 2, max_n / 2) * 2;
    //     if (n < N_MIN) n = N_MIN + (N_MIN % 2 == 0 ? 0 : 1);
        
    //     total_n += n;
        
    //     if (PRINT_N) {
    //         cout << n << "\n";
    //     }
        
    //     // 生成字符串
    //     string s;
    //     if (GENERATION_MODE == 0) {
    //         // 完全随机模式
    //         for (int i = 0; i < n; i++) {
    //             s += gen_char();
    //         }
    //     } else {
    //         s = gen_testcase(n);
    //     }
        
    //     cout << s << "\n";
    // }
    
    return 0;
}