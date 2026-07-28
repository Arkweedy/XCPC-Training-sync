# AGENTS.md — Tools/stress

本目录是 C++ 随机对拍工具工作区。本文件是面向 AI 的唯一详细操作规则；根目录 `AGENTS.md` 和 `stress-tool` skill 只保留入口。

## 适用范围与平台

- 配置、运行、复现、重测或清理对拍环境时，默认在 `Tools/stress/` 下工作。
- 使用 `stress.py` 统一完成编译、运行、比较和失败样例保存；除非用户明确要求，不要手写 PowerShell、Bash 对拍循环，也不要在仓库根目录或题目目录手动编译三份工作源码。
- `stress.py` 依赖 `os.setsid`、`resource`、进程组信号等 Linux 语义，并可调用 `gdb`。当前终端是 Windows PowerShell 时，优先切换到 WSL/Linux 运行。
- 无法使用 WSL/Linux 时，只做静态检查并说明平台限制；不要退而生成 `.exe` 或把临时编译产物留在仓库内。

## 文件与目录

- `stress.py`：统一的对拍命令行入口。
- `mycode.cpp`：被测程序。
- `std.cpp`：可信标准程序或暴力程序。
- `gen.cpp`：随机数据生成器，每次输出一组完整输入。
- `genlib.hpp`：可供 `gen.cpp` 引用的可选生成器工具库。
- `.stress/build/`：工具生成的可执行文件。
- `.stress/tmp/`：当前运行使用的临时输入输出。
- `.stress/last/`：最近一次进入运行阶段的失败或完成全部轮次的快照；编译失败 `CE` 不会更新这里。
- `.stress/cases/`：历史失败样例库。

`gen.cpp`、`std.cpp`、`mycode.cpp` 被 `.gitignore` 忽略，缺失不代表工具损坏。Git 不能可靠展示或恢复它们的内容；修改前必须先读取并保留用户已有代码，并从仓库根目录检查：

```bash
git status --short --ignored -- Tools/stress
```

## 标准工作流

1. 检查 `Tools/stress/` 当前状态，确认工作源码和历史 cases 是否属于用户已有内容。
2. 只按当前任务配置 `gen.cpp`、`std.cpp`、`mycode.cpp`，必要时使用 `genlib.hpp`。
3. 在 WSL/Linux 的 `Tools/stress/` 目录运行 `stress.py`。
4. 遇到运行阶段的首个非 AC 后，检查 `.stress/last/` 和新保存的 `.stress/cases/<case>/`；编译失败 `CE` 只检查保存的 case。
5. 修改代码后使用 `repro` 复现单个 case，或使用 `cases retest` 重测历史 cases。
6. 任务结束时只清理本轮可安全清理的生成物，并再次检查目录状态。

常用命令：

```bash
python3 stress.py run
python3 stress.py run -n 10000 --tl 2
python3 stress.py run --debug
python3 stress.py run --chk
python3 stress.py run --bt
python3 stress.py repro .stress/cases/<case-dir>
python3 stress.py cases list
python3 stress.py cases retest
python3 stress.py clean
```

## 运行语义

- `run` 会先编译 `gen.cpp`、`std.cpp`、`mycode.cpp`，再循环生成输入并运行标准程序与被测程序。
- AC 的判断条件是 `std` 与 `mycode` 的输出字节完全相同。token 或按行 diff 只用于定位和展示差异，不参与 AC 判定。
- 运行阶段的首个非 AC 会保存到 `.stress/cases/NN_TAG_timestamp/`，并更新 `.stress/last/`。
- `GEN_*`、`STD_*`、`MY_*` 分别表示生成器、标准程序、被测程序的运行错误；编译失败使用 `CE`，同样会保存历史 case。
- `repro` 只重新编译并运行 `std.cpp` 与 `mycode.cpp`，使用指定 case 的 `input.txt`，不会重新运行生成器。
- `repro` 不是纯只读操作：被测程序运行失败或输出不一致时，它会把 `repro_std.*`、`repro_my.*`、可能的 backtrace 或 `repro_report.txt` 写入指定 case。
- `cases retest` 会使用当前 `std.cpp` 和 `mycode.cpp` 重测 `.stress/cases/` 下所有包含 `input.txt` 的历史 case，并跳过没有输入文件的 case（例如 `CE`）。

## 清理与安全边界

- 优先使用 `python3 stress.py clean`。它只重建 `.stress/tmp/`、`.stress/build/`、`.stress/last/` 并重置 case 编号，保留 `.stress/cases/`。
- 不要删除 `.stress/cases/`。只有用户明确要求清空全部历史 cases 时，才可执行 `python3 stress.py cases clear --yes`。
- 不要覆盖或恢复不属于本轮任务的 `gen.cpp`、`std.cpp`、`mycode.cpp`；不要假设 Git 能找回被忽略工作文件的原内容。
- 手动清理前先列出目标目录，只精确删除本轮生成且确认无用的文件；不要使用宽泛通配符删除。
- 除非用户明确要求，不要修改 `stress.py`、`genlib.hpp`、`readme.md`、`feedback.md` 或历史 case 内容。
