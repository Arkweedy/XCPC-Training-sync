---
name: update-index
description: 用中文维护口胡训练记录的生成索引。适用于新记录归档后，按 OJ、tag、time、rating、误判类型更新 oral_training/views/。
---

# Update Index Skill

维护 `oral_training/views/` 下的生成索引。

## 唯一真源

canonical records 位于：

```text
oral_training/records/YYYY/YYYY-MM/*.md
```

索引必须从这些记录的 YAML front matter 生成，不要从旧索引反推。

## 需要维护的视图

- `oral_training/views/oj/*.md`
- `oral_training/views/tags/*.md`
- `oral_training/views/time/*.md`
- `oral_training/views/rating/*.md`

后续可选：

- `oral_training/summaries/by_mistake/*.md`
- `oral_training/summaries/by_tag/*.md`
- `oral_training/summaries/by_oj/*.md`

## 规则

- 不要在 views 里复制完整记录，只链接 canonical files。
- 表格保持紧凑。
- 若某个索引文件存在人工笔记区，不要覆盖人工笔记区。
- 若脚本可用，优先在仓库根目录运行：

```bash
python oral_training/scripts/index_records.py
```
