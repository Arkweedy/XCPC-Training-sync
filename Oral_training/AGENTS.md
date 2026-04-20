# AGENTS.md — oral_training

这是 `XCPC_Training` 仓库中的“口胡训练”模块，用于记录和评审算法题的初始思路。

## 语言约定

- 默认使用中文输出评审、总结、建议和说明。
- 术语可以中英混用，例如 `DSU-on-tree`、`gap analysis`、`metadata`，但主要解释应为中文。
- JSON / YAML 字段名保持英文，便于脚本处理。

## 模块目标

本模块不是单纯存题解，而是训练：

- 第一反应的题型识别；
- 快速排除错误算法；
- 发现证明缺口；
- 判断复杂度是否真实可过；
- 判断实现是否比赛可写；
- 通过长期归档发现自己的误判模式。

## 目录含义

- `inbox/`：待评审草稿。
- `records/`：单题记录的唯一真源。每题只在这里有一份 canonical record。
- `reviews/`：如果不想把评审追加到原记录，可把单独评审放这里。
- `summaries/`：周/月/OJ/标签/误判类型总结。
- `views/`：按 OJ、tag、time、rating 等生成的索引视图；不要复制完整记录。
- `taxonomy/`：标签体系、评分标准、metadata schema。
- `templates/`：新建记录和总结用的模板。
- `scripts/`：本地小脚本。

## 记录填写原则

默认模板是轻量版。用户可以只填写：

1. 题目/链接/题意简述；
2. 我的口胡；
3. 我不确定的点。

其他项都是可选项。未填写时，评审者应：

- 不要因为空项而拒绝评审；
- 明确说明“由于缺少约束/题面，以下判断基于假设”；
- 优先评价已有口胡中的方向、证明、复杂度、实现风险；
- 只追问那些确实会显著影响判断的信息。

## Canonical storage rule

单题记录按时间存储：

```text
records/YYYY/YYYY-MM/YYYY-MM-DD_SOURCE_PROBLEM_SLUG.md
```

OJ、算法标签、rating、误判类型等导航视角应由 `views/` 自动生成，不要把完整记录复制到多个地方。

## 评审规则

评审一条记录时：

1. 保留原始口胡。
2. 评审追加到 `## Agent Review` 或另存 `reviews/`。
3. 默认中文输出。
4. 使用 `taxonomy/` 中的标签和风险尺度。
5. JSON metadata 保持机器可读。
6. 若已经提供题解/AC 解法，使用 gap-analysis，不要做伪 first-look review。

## Metadata 最小要求

每条记录建议有 YAML front matter，但最小只需要：

```yaml
date: YYYY-MM-DD
source: unknown
problem: unknown
status: draft
```

推荐字段见 `taxonomy/metadata_schema.md`。

## 不要做

- 不要覆盖 `locked: true` 的记录。
- 不要未经用户要求移动历史记录。
- 不要把完整记录复制到 `views/`。
- 不要把题解后的认识混入初始口胡。
- 不要因为模板空项较多就强迫用户补全。
