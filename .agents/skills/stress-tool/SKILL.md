---
name: stress-tool
description: 用中文安全使用本仓库 Tools/stress/stress.py 对拍库。适用于需要配置 mycode.cpp/std.cpp/gen.cpp、运行随机对拍、复现保存 case、清理 stress 临时目录、或避免手动编译产生垃圾文件的任务。
---

# Stress Tool

## 核心原则

- 默认在 `Tools/stress/` 下工作；不要在仓库根目录或题目目录手动编译 `gen.cpp/std.cpp/mycode.cpp`。
- 使用 `stress.py` 统一编译、运行、比较、保存失败样例；除非用户明确要求，不要手写 PowerShell/Bash 对拍循环。
- 修改 `gen.cpp/std.cpp/mycode.cpp` 前先检查 `git status --short --ignored Tools/stress`，确认哪些是用户已有修改。
- 清理时优先使用 `python3 stress.py clean`，它只清 `.stress/tmp`、`.stress/build`、`.stress/last` 并重置 case id，保留 `.stress/cases`。
- 不要删除 `.stress/cases`，除非用户明确要求并允许使用 `python3 stress.py cases clear --yes`。

## 文件约定

- `mycode.cpp`：被测代码。
- `std.cpp`：可信标准程序或暴力程序。
- `gen.cpp`：随机数据生成器，输出一组完整输入。
- `genlib.hpp`：可选生成器工具库，可以在 `gen.cpp` 中 `#include "genlib.hpp"`。
- `.stress/build/`：`stress.py` 生成的可执行文件。
- `.stress/tmp/`：当前轮次临时输入输出。
- `.stress/last/`：最近一次失败或完整运行的输入输出快照。
- `.stress/cases/`：历史失败样例库。

## 常用命令

在 `Tools/stress/` 目录运行：

```bash
python3 stress.py run
python3 stress.py run -n 10000 --tl 2
python3 stress.py run --debug
python3 stress.py run --chk
python3 stress.py run --bt
python3 stress.py repro .stress/cases/05_WA_20260403_014240
python3 stress.py cases list
python3 stress.py cases retest
python3 stress.py clean
```

## 运行语义

- `run` 会先编译 `gen.cpp/std.cpp/mycode.cpp`，然后循环：运行生成器、运行 std、运行 mycode、按 token 比较输出。
- 首个非 AC 会保存到 `.stress/cases/NN_TAG_timestamp/`，并更新 `.stress/last/`。
- `WA` 报告会指出第一个不同 token 的行列和上下文；大输出会切到按行 diff。
- `GEN_*`、`STD_*`、`MY_*` 分别表示生成器、标准程序、被测程序出错。
- `CE` 会保存编译命令和编译日志尾部到 case 的 `meta.json/report.txt`。
- `repro` 只重新编译并运行 `std.cpp/mycode.cpp`，使用指定 case 的 `input.txt`，不会重新运行生成器。
- `cases retest` 会用当前 `std.cpp/mycode.cpp` 重测 `.stress/cases/` 下所有历史 case。

## 调试选项

- `--debug`：三份程序用 `-O0 -g -fno-omit-frame-pointer -fsanitize=address,undefined` 编译。
- `--chk`：仅给 `mycode.cpp` 加 libstdc++ debug/assertion 宏，适合把越界迭代器等问题变成 RE。
- `--bt`：在被测程序信号崩溃且 stderr 没有定位时，用 gdb 生成 backtrace；非 debug 模式下会给 std/mycode 补 `-g -fno-omit-frame-pointer`。
- `--ml`：限制 std/mycode 的内存 MB。
- `--ml-gen`：限制生成器内存 MB。

## 平台注意

- 当前 `stress.py` 使用 `preexec_fn`、`os.setsid`、`resource`、`gdb` 等 Linux/WSL 语义；在 Windows PowerShell 下可能无法正常运行。
- 如果当前 shell 是 Windows PowerShell，优先切到 WSL/Linux 环境运行 `python3 stress.py ...`。不要退而手动生成 `.exe` 做临时循环，除非用户明确允许。
- 若必须在非 Linux 环境诊断，只能做静态检查或说明平台限制；不要把手动编译产物留在 `Tools/stress/`。

## 清理规则

- 删除自己产生的额外文件前，先列出 `git status --short --ignored Tools/stress` 和 `Get-ChildItem Tools/stress -Force`。
- 精确删除本轮手动产生的文件，例如 `gen.exe/std.exe/mycode.exe/input.txt/std.out/my.out`，不要通配删除。
- 如果需要恢复 `gen.cpp/std.cpp/mycode.cpp`，只恢复自己刚刚修改过的文件；不要改动用户已有 case 或 unrelated 文件。
- 清理后再次确认 `git diff -- Tools/stress/gen.cpp Tools/stress/std.cpp Tools/stress/mycode.cpp`。
