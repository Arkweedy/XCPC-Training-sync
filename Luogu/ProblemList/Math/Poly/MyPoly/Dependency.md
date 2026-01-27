# 多项式模板依赖表（抄代码用）

> 说明：每个「块」是一段可以整体复制的代码。  
> 依赖写成 `依赖：A + D + ...`，表示抄这个块前必须先抄对应依赖块。

---

## A. Mod 基础（必备）
**内容：**
- `constexpr int P, G`
- `power(a,p) mod P`
- `power(a,p,M)`
- `inv(a)`

**依赖：** 无

---

## B. Comb 预处理（可选但建议）
**内容：**
- `struct Comb` + 全局 `comb`

**依赖：** A

> 常用于：`integr()`、`exp2()`、组合数/阶乘等。

---

## C. 常数项开方（现在为 BSGS，以后换 Cipolla）
**内容：**
- `bsgs`
- `Fsqrt`

**依赖：** A

---

## D. NTT 根表
**内容：**
- `MAX_LEN`（以及可选 `Q`）
- `omega()`
- `W`

**依赖：** A

---

## E. NTT 变换
**内容：**
- `dft(vector<int>&)`
- `idft(vector<int>&)`

**依赖：** A + D

---

# poly 类分层（P0~P5）

## P0. poly 载体与基础运算
**内容：**
- `class poly : public vector<int>`
- 构造函数
- `+ , - , unary-`
- 标量 `* , /`（`/ int`）

**依赖：** A

---

## P1. poly 乘法（NTT/朴素）
**内容：**
- `friend poly operator*(poly, poly)`（含 NTT）

**依赖：** P0 + E

---

## P2. poly 基础工具
**内容：**
- `shift`
- `trunc`
- `deriv`
- `integr`（若用 comb）
- `rev`

**依赖：**
- `shift/trunc/deriv/rev`：P0
- `integr`（你当前实现）：P0 + B  
  （如果改回用 `inv(i+1)` 则是 P0 + A）

---

## P3. 牛顿系与初等函数
**内容：**
- `inv(m)`
- `log(m)`
- `exp(m)`
- `exp2(m)`（CDQ）
- `pow(...)`

**依赖：**
- `inv/log/exp/pow`：P1 + P2 + A
- `exp2`（你当前实现用 `comb.inv`）：P1 + P2 + B

---

## P4. sqrt
**内容：**
- `sqrt(m)`

**依赖：** P3 + C + A

---

## P5. 转置乘法与多点求值
**内容：**
- `mulT`
- `eval(vector<int>)`

**依赖：** P1 + P2 + P3  
（eval 内部会用 `m[1].inv(n)`，所以隐含依赖 `poly::inv`）

---

# 外部算法（X1~X6）

## X1. 拉格朗日插值
**内容：**
- `poly lagrange(vector<int>x, vector<int>y)`

**依赖：** P1 + P2(deriv) + P5(eval) + A

---

## X2. 连续点值平移
**内容：**
- `vector<int> valueShift(const vector<int>& v, int c)`

**依赖：** P1 + A  
（你当前版本局部算 `fac/invfac`，不依赖 Comb）

---

## X3. 泰勒平移（系数平移）
**内容：**
- `poly taylorShift(poly& f, int c)`

**依赖：** P5(mulT) + A  
（你当前版本局部算 `fac/invfac`，不依赖 Comb）

---

## X4. Bostan–Mori 与线性递推
**内容：**
- `bostanMori(p,q,n)`
- `linearRecurrence(a,c,n)`

**依赖：** P1 + A

---

## X5. Berlekamp–Massey
**内容：**
- `berlekampMassey(s)`

**依赖：** A + P0  
（不需要 NTT，不需要 P1/P3）

---

## X6. 复合 / 复合逆（composition 命名空间）
**内容：**
- `composition::biMul/.../Comp/comp`
- `powerProjection`
- `compInv`

**依赖：** A + P1 + P2 + P3  
（通常还会顺带需要 B；你的实现里 compInv/log/exp2 走 comb 会依赖 B）

---

# 常见“最小抄写清单”（按需求）

## 1) 只要卷积/乘法
- A + D + E + P0 + P1

## 2) inv/log/exp/pow 全家桶
- (1) + P2 + P3 + B（因为 integr/exp2 用 comb）

## 3) sqrt
- (2) + C + P4

## 4) 多点求值 eval / 插值 lagrange
- eval： (2) + P5  
- lagrange： eval + X1

## 5) Bostan–Mori / 线性递推
- A + D + E + P0 + P1 + X4

## 6) BM（最小多项式/线性递推）
- A + P0 + X5
