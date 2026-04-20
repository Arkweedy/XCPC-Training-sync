#!/usr/bin/env python3
"""Pack one ISO week's records into a Markdown bundle for Codex weekly summary."""

from __future__ import annotations

import argparse
import datetime as dt
from pathlib import Path

from _record_utils import iso_week_range, iter_records, meta_date

ROOT = Path(__file__).resolve().parents[2]
MODULE = ROOT / "oral_training"
RECORDS = MODULE / "records"
OUT_DIR = MODULE / "summaries" / "weekly"


def current_iso_week() -> str:
    today = dt.date.today()
    year, week, _ = today.isocalendar()
    return f"{year}-W{week:02d}"


def main() -> None:
    parser = argparse.ArgumentParser(description="Create a weekly bundle from oral training records.")
    parser.add_argument("--week", default=current_iso_week(), help="ISO week, e.g. 2026-W16.")
    parser.add_argument("--output", default="", help="Output bundle path.")
    args = parser.parse_args()

    start, end = iso_week_range(args.week)
    selected = []
    for path, meta in iter_records(RECORDS):
        d = meta_date(meta)
        if d is not None and start <= d <= end:
            selected.append((path, meta))

    OUT_DIR.mkdir(parents=True, exist_ok=True)
    out = Path(args.output) if args.output else OUT_DIR / f"{args.week}_bundle.md"
    if not out.is_absolute():
        out = ROOT / out

    lines: list[str] = []
    lines.append(f"# Weekly Bundle: {args.week}\n")
    lines.append(f"Date range: {start.isoformat()} ~ {end.isoformat()}\n")
    lines.append(f"Problem count: {len(selected)}\n")

    for idx, (path, meta) in enumerate(selected, 1):
        rel = path.relative_to(ROOT).as_posix()
        title = meta.get("title") or meta.get("problem") or path.stem
        lines.append("\n---\n")
        lines.append(f"## {idx}. {title}\n")
        lines.append(f"- File: `{rel}`")
        lines.append(f"- Source: {meta.get('source', '')}")
        lines.append(f"- Problem: {meta.get('problem', '')}")
        lines.append(f"- Verdict: {meta.get('verdict', '')}")
        lines.append(f"- Misjudgment tags: {meta.get('misjudgment_tags', [])}")
        lines.append("")
        lines.append(path.read_text(encoding="utf-8"))

    out.write_text("\n".join(lines), encoding="utf-8")
    print(out.relative_to(ROOT))


if __name__ == "__main__":
    main()
