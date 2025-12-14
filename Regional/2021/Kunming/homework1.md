# 作业1

## 第 1 题

对给定类型为 `int list` 的 `L`，各模式匹配结果如下：

| 模式 | 能否匹配 `int list` | 说明 / 该模式自身类型 |
|---|---|---|
| `x :: L` | 可以 | 匹配非空 `int list`；`x : int`，`L : int list` |
| `_ :: _` | 可以 | 匹配非空 `’a list`（此处可实例化为 `int list`）|
| `x :: (y :: L)` | 可以 | 匹配长度 ≥ 2 的 `int list`；`x,y : int`，`L : int list` |
| `(x :: y) :: L` | 不行 | 该模式类型为 **列表的列表**：`(’a list) list`（若 `x,y : int`，则为 `int list list`），不可能与 `int list` 匹配 |
| `[x, y]` | 可以 | 仅匹配长度 **恰为 2** 的 `int list`；`x,y : int` |

---

## 第 2 题

- “长度为 3 的表”：  
  `[_ , _ , _]` 或等价的 `a :: b :: c :: []`

- “长度为 2 或 3 的表”：  
  **不存在单个模式**同时精确刻画两种长度；需在函数分支/`case` 中使用两个模式：`[a,b]` 与 `[a,b,c]`。

- “非空的二元组表（list of pairs）”：  
  `( _ , _ ) :: _`

- “两个分量均为非空表的二元组”：  
  `( _ :: _ , _ :: _ )`

---

## 第 3 题

给定程序片段中：

- 第 4 行的 `x`：类型 `int`，值 `2`（在 `g` 的内层 `let` 中首次绑定，后续局部可见）
- 第 5 行的 `m`：类型 `real`，值 `6.2 * real 2 = 12.4`（此处引用的是第 4 行的 `x = 2`）
- 第 6 行再次绑定的 `x`：类型 `int`，值 `9001`（**遮蔽** 第 4 行的 `x`，但对已求值的 `m` 无影响）

`assemble (x, 3.0)` 的求值（第 14 行；外层 `x = 3`）：
- 内层得到 `g = (m * y_param) - m = 12.4 * 3.0 - 12.4 = 24.8`
- 外层结果 `x + trunc g = 3 + 24 = 27`

因此第 14 行表达式的结果为 **27**。

---

## 第 4 题

### 代码

```sml
(* zip : string list * int list -> (string * int) list *)
fun zip (xs, ys) =
  case (xs, ys) of
      (x::xs', y::ys') => (x, y) :: zip (xs', ys')
    | _                 => []

(* unzip : (string * int) list -> string list * int list *)
fun unzip ps =
  let
    fun loop ([],    accS, accI) = (List.rev accS, List.rev accI)
      | loop ((s,i)::rest, accS, accI) = loop (rest, s::accS, i::accI)
  in
    loop (ps, [], [])
  end
```
命题：“对任意 L1 : string list 与 L2 : int list，是否有 unzip (zip (L1, L2)) = (L1, L2)？

~~~
Proof:
不恒成立。当两表长度不同，zip 会截断到 min(len L1, len L2)：
例：L1 = ["a"]，L2 = [1,2]，则
zip (L1, L2) = [("a",1)]，unzip 后为 (["a"], [1]) ≠ (L1, L2)。

充要条件：当且仅当 len L1 = len L2 时，上述等式成立。
证明思路（结构归纳）：对等长表成对归纳：

基础步：([], []) 成立。

归纳步：设 (xs, ys) 等长且命题对其成立。对 x::xs, y::ys：
zip (x::xs, y::ys) = (x,y) :: zip (xs, ys)；
unzip 后为 (x::xs, y::ys)，由归纳假设得证。
~~~

## 第5题:
给定代码片段（节选）存在如下问题：
1. f 的第二个分支缺少分支符号 |：应写作 | f _ = 4

2. circ 中字面量 2 为 int，与 real 相乘类型不一致：应写 2.0

3. semicirc 的定义：少写 fun 与实参列表（r 未绑定）

4. 将 pi 误写为 pie

5. 类型标注位置不当:area 的参数写成 int，与 pi : real 连乘类型不一致；需将参数改为 real，或显式转换

更正：
```sml
val pi : real = 3.14159

fun fact 0 = 1
  | fact n = n * fact (n - 1)

fun f 3 = 9
  | f _ = 4

fun circ (r : real) : real = 2.0 * pi * r

fun semicirc (r : real) : real = pi * r  (* 半圆长度，依题意可调整 *)

fun area (r : real) : real = pi * r * r

```

## 第6题:
1. 朴素递归：
时间复杂度$T(n) = \phi^n$，其中$\phi = \frac{1 + \sqrt 5}{2}$
证明：
由递推式：$$T(n) = T(n - 1) + T(n - 2)$$和初始条件：$T(1) = T(2) = 1$
解特征方程$r^2 - r - 1 = 0$
可得通解$T(n)=Aφ^n+Bψ^n$，其中$\phi = \frac{1 + \sqrt 5}{2}, \psi = \frac{1 - \sqrt 5}{2}$
空间：递归栈深为$O(n)$

2. 线性递推
时间：$Θ(n)$。
空间：栈深 $Θ(n)$，非尾递归。
可改写为尾递归保持 $O(1)$ 空间。

3. 改进：可以做到对数级
    ```sml
    fun fibFast n =
    let
        fun dbl 0 = (0, 1)
        | dbl k =
            let
                val (a, b) = dbl (k div 2)
                val c = a * (2 * b - a)
                val d = a * a + b * b
            in
                if k mod 2 = 0 then (c, d) else (d, c + d)
            end
    in
        #1 (dbl n)
    end
    ```
    也可以直接用矩阵快速幂来计算。

