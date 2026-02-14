#!/bin/bash

# 创建存放可执行文件和输入输出文件的目录
mkdir -p execute
mkdir -p io

# 编译三个C++文件到execute目录
echo "正在编译程序..."
g++ -std=c++23 -o execute/mycode mycode.cpp
if [ $? -ne 0 ]; then
    echo "mycode.cpp 编译失败!"
    exit 1
fi

g++ -std=c++23 -o execute/std std.cpp
if [ $? -ne 0 ]; then
    echo "std.cpp 编译失败!"
    exit 1
fi

g++ -std=c++23 -o execute/make_data make_data.cpp
if [ $? -ne 0 ]; then
    echo "make_data.cpp 编译失败!"
    exit 1
fi

echo "编译成功，开始对拍..."
test_case=1

# 无限循环进行对拍，直到找到WA
while true; do
    # 生成测试数据到io目录
    execute/make_data > io/data.in
    
    # 运行测试程序，从io目录读取输入，输出到io目录
    execute/mycode < io/data.in > io/mycode.out
    execute/std < io/data.in > io/std.out
    
    # 比较输出结果
    if diff -q io/mycode.out io/std.out > /dev/null; then
        echo "test case $test_case AC!"
    else
        echo "test case $test_case WA!"
        # 保存错误数据
        cp io/data.in io/wa.in
        echo "错误数据已保存到 io/wa.in"
        echo "你的程序输出在 io/mycode.out"
        echo "标准程序输出在 io/std.out"
        break
    fi
    
    test_case=$((test_case + 1))
done