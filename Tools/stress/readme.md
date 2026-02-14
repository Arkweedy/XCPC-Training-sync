python3 stress.py run

python3 stress.py cases clear --yes

python3 stress.py cases retest

python3 stress.py clean

1) 常用参数：
-n <int>：最多轮数（默认 10000）
--tl <float>：每次运行时间限制秒（默认 5.0s）
--ml <int>：std/mycode 内存限制 MB（默认不限制）
--ml-gen <int>：gen 内存限制 MB（默认不限制）
--chk：mycode 开 libstdc++ debug checks（很多“越界/迭代器错误”从 WA 变 RE）
--debug：ASan/UBSan（更容易给出 file:line）
--bt：当 RE 且没有行号 时自动跑 gdb backtrace，尽力定位 mycode.cpp:line
推荐组合：
怀疑 UB：python3 stress.py run --debug
怀疑容器越界/迭代器：python3 stress.py run --chk
怀疑除 0/段错误但没行号：python3 stress.py run --bt（需要 gdb）

2) 复现某个 case
python3 stress.py repro .stress/cases/04_MY_RE_20260214_181425
参数同 run：--tl / --ml / --debug / --chk / --bt

3) 清理（保留历史 cases，但重置编号 & 清空 build/tmp/last）
python3 stress.py clean

4) 管理历史 cases
列表：
python3 stress.py cases list
清空（需要确认）：
python3 stress.py cases clear --yes
全部重测（用当前 mycode/std 重新跑每个 case 的 input.txt）：
python3 stress.py cases retest
可加：
--tl / --ml / --debug / --chk / --bt