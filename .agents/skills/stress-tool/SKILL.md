---
name: stress-tool
description: 用中文安全使用本仓库 Tools/stress/stress.py 对拍库。适用于需要配置 mycode.cpp/std.cpp/gen.cpp、运行随机对拍、复现保存 case、清理 stress 临时目录、或避免手动编译产生垃圾文件的任务。
---

# Stress Tool

1. 执行任何对拍操作前，完整读取 [`Tools/stress/AGENTS.md`](../../../Tools/stress/AGENTS.md)。
2. 将该文件作为 `Tools/stress/` 配置、运行、复现、重测和清理的唯一详细规则源。
3. 在 `Tools/stress/` 内工作并严格遵循其平台限制与数据保护边界；无法读取该文件时停止操作并说明原因。
