```c++
// max Cartesian tree, ties broken to the right
    vector<int> lc(n, -1), rc(n, -1), fa(n, -1), stk;
    stk.reserve(n);

    for (int i = 0; i < n; i++) {
        int last = -1;
        while (!stk.empty() && a[stk.back()] <= a[i]) {
            last = stk.back();
            stk.pop_back();
        }
        if (last != -1) {
            lc[i] = last;
            fa[last] = i;
        }
        if (!stk.empty()) {
            rc[stk.back()] = i;
            fa[i] = stk.back();
        }
        stk.push_back(i);
    }

    int root = stk.front();

    vector<int> sz(n, 0);
```

正确性分析：
维护当前的右链，右儿子会被覆盖更新
弹出一段右链后，最大的点作为新左子树的根，即代码中的`last`