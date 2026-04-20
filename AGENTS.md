# AGENTS.md — XCPC_Training

这个仓库是 XCPC / ICPC / Codeforces / AtCoder 等算法训练工作区，包含比赛代码、模板、笔记、工具和训练记录。

## 全仓库原则

- 默认使用中文与用户交流；除非用户要求英文，评审、总结、解释都尽量使用中文。
- 对历史比赛代码、题解笔记、模板文件保持克制：没有明确要求时，不要批量重构、改名、移动或“清理”。
- 训练记录、总结、复盘优先使用 Markdown。
- 竞赛代码示例默认使用 C++。
- 自动生成内容应与手写题解/代码分离，避免污染原有比赛目录。

## 口胡训练模块

口胡训练模块位于 `Oral_training/`。

它用于：

- 评审一道题的初始口胡/算法想法；
- 判断正确性、复杂度、证明、实现难度和比赛可写性风险；
- 将首想法与题解/AC 解法进行 gap analysis；
- 做周总结、月总结和误判模式分析；
- 维护按 OJ、算法标签、时间、难度、误判类型的多视角索引。

当用户要求“口胡评审 / 思路评审 / gap analysis / 周总结 / 更新索引”时，优先使用 `.agents/skills/` 下的 skills：

- `oral-review`：单题口胡评审；
- `gap-analysis`：首想法与题解/AC 解法的差距分析；
- `weekly-summary`：多条记录的周总结；
- `update-index`：维护 `Oral_training/views/` 下的生成索引。

## 口胡训练记录安全规则

- 必须保留用户原始口胡，不要直接改写原文，除非用户明确要求。
- 评审内容应追加到 `## Agent Review`，或保存到 `Oral_training/reviews/`。
- 如果记录中存在 `locked: true`，没有明确许可不要修改。
- 模板中未填写的项视为“未知/未提供”，不要因此拒绝评审；应基于已有信息给出 best-effort 反馈，并指出哪些缺失信息最影响判断。
- 不要把已经看过题解后的结论伪装成 first-look review；若有题解/正解摘要，应使用 `gap-analysis`。

## 推荐工作流

创建新口胡记录：

1. 在根目录运行 `python Oral_training/scripts/new_record.py ...`，生成 `Oral_training/inbox/` 下的草稿。
2. 用户只需填写最小必填项：题目、口胡思路、薄弱点/疑问。其他项可空。
3. 使用 `oral-review` skill 评审。
4. 将评审后的记录归档到 `Oral_training/records/YYYY/YYYY-MM/`。
5. 需要时更新 `Oral_training/views/` 下的索引。

做周总结：

1. 收集 `Oral_training/records/` 中本周记录。
2. 总结模式，而不是逐题复述。
3. 保存到 `Oral_training/summaries/weekly/`。
