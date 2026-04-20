# Oral Training / 口胡训练

这个模块用于记录和评审算法题的初始口胡。目标不是写漂亮题解，而是训练“看到题以后如何判断方向、排除错误算法、估计实现风险”。

## 最小日常流程

在 `XCPC_Training/` 根目录运行：

```bash
python oral_training/scripts/new_record.py --source AtCoder --contest ABC454 --problem ABC454G --title "my first oral idea"
```

然后编辑生成的 `oral_training/inbox/` 文件。你只需要填三块：

1. `题目概况`：链接/题意/关键约束，能写多少写多少；
2. `我的口胡`：第一反应、核心算法想法；
3. `我不确定的点`：正确性、复杂度、实现、是否有更简单做法。

其他空项不会影响评审。Codex 应该基于已有信息做 best-effort 反馈，而不是要求你补全所有模板字段。

## 让 Codex 评审

在根目录向 Codex 说：

```text
使用 oral-review skill，评审 oral_training/inbox/<file>.md，并用中文输出。
```

如果需要把评审追加到文件：

```text
使用 oral-review skill 评审 oral_training/inbox/<file>.md，把评审追加到 ## Agent Review 下，并保留我的原始口胡不变。
```

看过题解或 AC 解法后：

```text
使用 gap-analysis skill，比较我的首想法和下面的题解摘要：...
```

## 周总结

先打包某周记录：

```bash
python oral_training/scripts/pack_week.py --week 2026-W16
```

再让 Codex：

```text
使用 weekly-summary skill，总结 oral_training/summaries/weekly/2026-W16_bundle.md，并保存到 oral_training/summaries/weekly/2026-W16.md。
```

## 数据模型

单题记录只有一份 canonical record，按时间存放：

```text
oral_training/records/YYYY/YYYY-MM/YYYY-MM-DD_SOURCE_PROBLEM.md
```

其他视角都生成索引，不复制完整记录：

- 按 OJ：`views/oj/`
- 按算法标签：`views/tags/`
- 按时间：`views/time/`
- 按难度：`views/rating/`

## 模板选择

默认模板 `templates/oral_record.md` 是轻量版。

如果某道题你想做完整复盘，可以复制：

```text
templates/oral_record_full.md
```

完整模板包含更细的题面、证明、复杂度和实现风险栏，但不是日常必需。
