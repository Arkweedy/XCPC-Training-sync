# AGENTS.md — XCPC_Training

这个仓库是 XCPC / ICPC / Codeforces / AtCoder 等算法竞赛的个人训练工作区，包含比赛代码、算法模板、笔记、训练工具和复盘记录。

## 全仓库原则

- 默认使用中文与用户交流；除非用户要求英文，评审、总结和解释都尽量使用中文。
- 处理目标目录时，先读取并遵循离目标文件最近的 `AGENTS.md`；更具体的目录规则优先于本文件。
- 对历史比赛代码、题解笔记和模板文件保持克制；没有明确要求时，不要批量重构、改名、移动或“清理”。
- 训练记录、总结和复盘优先使用 Markdown。
- 竞赛代码及示例默认使用 C++。
- 自动生成内容应与手写题解、代码分离，避免污染原有比赛目录。

## 目录结构

- `Atcoder/`、`Codeforces/`、`HDU/`、`Luogu/`、`NC/`、`Ucup/`：按 OJ 或赛事系列归档的训练与比赛代码。
- `Invitational/`、`Provincial/`、`Regional/`、`Others/`：邀请赛、省赛、区域赛及其他赛事代码。
- `Misc/`：暂未归入固定平台或赛事分类的零散训练代码。
- `Algorithms/`：按算法主题整理的学习代码与少量笔记。
- `Templates/`：比赛中可复用的算法与数据结构模板。
- `Notes/`：算法、题目、杂项和 LaTeX 相关笔记。
- `Tools/`：本地训练辅助工具，包括对拍、数据处理和比赛环境辅助工具。
- `SPJ/`：特殊判题、数据生成及相关实验代码。
- `Oral_training/`：口胡训练记录、评审、索引、模板和脚本。
- `.agents/skills/`：本仓库本地注册的 AI skills。
- `.codex/`：本仓库的 Codex 项目级配置。
- `tmp/`：临时工作目录，不作为长期内容归档位置。
- `.cph-ng/`、`.vscode/`、`.crossnote/`：本地生成或编辑器配置目录，不作为仓库知识资产。

## 模块入口

### 口胡训练

- 口胡训练的详细规则见 `Oral_training/AGENTS.md`，日常使用说明见 `Oral_training/README.md`。
- 单题口胡评审、正解差距分析、周总结和索引维护分别使用仓库本地的 `oral-review`、`gap-analysis`、`weekly-summary`、`update-index` skill。

### 对拍工具

- `Tools/stress/` 是 C++ 随机对拍工具目录。
- 配置、运行、复现或清理对拍环境时，使用仓库本地的 `stress-tool` skill，并遵循 `Tools/stress/AGENTS.md`。
