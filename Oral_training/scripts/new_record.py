#!/usr/bin/env python3
"""新建一条口胡训练草稿。

默认使用轻量中文模板。示例：

    python oral_training/scripts/new_record.py --source AtCoder --contest ABC454 --problem ABC454G --title "my first oral idea"

若想使用更完整的复盘模板：

    python oral_training/scripts/new_record.py --source Codeforces --problem CF1854C --full
"""

from __future__ import annotations

import argparse
import datetime as dt
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MODULE = ROOT / "oral_training"
INBOX = MODULE / "inbox"


def slugify(text: str) -> str:
    text = text.strip().replace(" ", "_")
    text = re.sub(r"[^A-Za-z0-9_+.-]+", "", text)
    text = re.sub(r"_+", "_", text)
    return text.strip("_") or "unknown"


def fill_template(template: str, values: dict[str, str]) -> str:
    for key, value in values.items():
        template = template.replace("{{" + key + "}}", value)
    return template


def main() -> None:
    parser = argparse.ArgumentParser(description="Create a new oral training record draft.")
    parser.add_argument("--date", default=dt.date.today().isoformat(), help="Date in YYYY-MM-DD format.")
    parser.add_argument("--source", default="unknown", help="OJ/source, e.g. Codeforces, AtCoder, ICPC.")
    parser.add_argument("--contest", default="", help="Contest name or id.")
    parser.add_argument("--problem", default="unknown", help="Problem id, e.g. CF1854C or ABC453F.")
    parser.add_argument("--title", default="", help="Problem title or short note title.")
    parser.add_argument("--url", default="", help="Problem URL.")
    parser.add_argument("--rating", default="", help="Optional rating/difficulty.")
    parser.add_argument("--full", action="store_true", help="Use the full detailed template instead of the lightweight default.")
    parser.add_argument("--output", default="", help="Optional output path. Defaults to oral_training/inbox/...")
    args = parser.parse_args()

    try:
        dt.date.fromisoformat(args.date)
    except ValueError as exc:
        raise SystemExit(f"Invalid --date {args.date!r}; expected YYYY-MM-DD") from exc

    template_name = "oral_record_full.md" if args.full else "oral_record.md"
    template_path = MODULE / "templates" / template_name
    if not template_path.exists():
        raise SystemExit(f"Template not found: {template_path}")

    source_slug = slugify(args.source)
    problem_slug = slugify(args.problem)
    title = args.title.strip() or args.problem.strip() or "Untitled"
    display_name = f"{args.source} {args.problem} - {title}".strip(" -")

    values = {
        "date": args.date,
        "source": args.source,
        "contest": args.contest,
        "problem": args.problem,
        "title": title.replace('"', '\\"'),
        "url": args.url,
        "rating": args.rating,
        "display_name": display_name,
    }

    content = fill_template(template_path.read_text(encoding="utf-8"), values)

    if args.output:
        out = Path(args.output)
        if not out.is_absolute():
            out = ROOT / out
    else:
        out = INBOX / f"{args.date}_{source_slug}_{problem_slug}.md"

    out.parent.mkdir(parents=True, exist_ok=True)
    if out.exists():
        raise SystemExit(f"Refusing to overwrite existing file: {out}")

    out.write_text(content, encoding="utf-8")
    print(out.relative_to(ROOT))


if __name__ == "__main__":
    main()
