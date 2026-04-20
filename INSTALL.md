# 安装到 XCPC_Training

把本包内容复制到现有 `XCPC_Training/` 根目录。

预期新增：

```text
AGENTS.md
.codex/config.toml
.agents/skills/
oral_training/
```

如果你的仓库已经有 `AGENTS.md`，不要直接覆盖；把本包中和 oral-training 相关的规则合并进去即可。

## 第一次使用

在 `XCPC_Training/` 根目录运行：

```bash
python oral_training/scripts/new_record.py --source AtCoder --contest ABC454 --problem ABC454G --title "my first oral idea"
```

然后编辑 `oral_training/inbox/` 下生成的文件。默认模板是轻量版，只需填写：

- 题目概况；
- 我的口胡；
- 我不确定的点。

让 Codex 评审：

```text
使用 oral-review skill，评审 oral_training/inbox/<file>.md，并用中文输出。
```

## 生成索引

归档记录后，在根目录运行：

```bash
python oral_training/scripts/index_records.py
```

## 打包周记录

```bash
python oral_training/scripts/pack_week.py --week 2026-W16
```
