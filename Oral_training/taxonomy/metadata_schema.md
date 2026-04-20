# Metadata Schema / 元数据规范

每条 canonical record 建议以 YAML front matter 开头。

## 最小字段

```yaml
date: YYYY-MM-DD
source: unknown
problem: unknown
status: draft
```

## 推荐字段

```yaml
date: 2026-04-19
source: AtCoder
contest: ABC454
problem: G
title: "Problem title"
url: ""
rating:
status: draft # draft | reviewed | gap_analyzed | summarized
initial_tags: []
official_tags: []
misjudgment_tags: []
verdict: # likely_correct | salvageable | high_risk | likely_wrong | insufficient_info
confidence: # low | medium | high
correctness_risk:
complexity_risk:
implementation_risk:
contest_writability: # recommended | acceptable | risky | not_recommended
missed_signals: []
missing_info: []
one_line_review: ""
locked: false
```

## 填写原则

- 字段可以为空。
- 空字段表示“暂时未知”，不表示记录无效。
- 评审后可以由 agent 补充 `verdict`、`risk`、`misjudgment_tags` 等。
- 原始口胡内容不要因为 metadata 更新而被改写。

## Source naming

建议稳定使用：

- `Codeforces`
- `AtCoder`
- `Luogu`
- `HDU`
- `NC`
- `ICPC`
- `CCPC`
- `Ucup`
- `Misc`

## 状态流转

```text
draft -> reviewed -> gap_analyzed -> summarized
```

没有看题解时，可以只停留在 `reviewed`。

## 路径约定

canonical records：

```text
oral_training/records/YYYY/YYYY-MM/YYYY-MM-DD_SOURCE_PROBLEM_SLUG.md
```

例：

```text
oral_training/records/2026/2026-04/2026-04-19_Codeforces_CF1854C.md
oral_training/records/2026/2026-04/2026-04-20_AtCoder_ABC453F.md
```
