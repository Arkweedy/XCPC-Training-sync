#include <bits/stdc++.h>
#include <genlib.hpp>
using namespace std;
using i64 = long long;
using u32 = usigned int;
using u64 = unsigned long long;

int main()
{
    int n = 100;
    cout << n << endl;
    gen::io::print_vec(cout, gen::seq::array_distinct(n, 1, n));
    gen::io::print_graph(cout, gen::graph::tree_prufer(n, 1, 0));
    return 0;
}