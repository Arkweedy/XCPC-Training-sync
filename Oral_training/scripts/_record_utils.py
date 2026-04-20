from __future__ import annotations

import datetime as dt
import re
from pathlib import Path
from typing import Any

FRONT_MATTER_RE = re.compile(r"\A---\s*\n(.*?)\n---\s*\n", re.DOTALL)


def parse_scalar(value: str) -> Any:
    value = value.strip()
    if value == "":
        return ""
    if value in {"true", "True"}:
        return True
    if value in {"false", "False"}:
        return False
    if value.startswith("[") and value.endswith("]"):
        inner = value[1:-1].strip()
        if not inner:
            return []
        return [x.strip().strip('"\'') for x in inner.split(",") if x.strip()]
    if (value.startswith('"') and value.endswith('"')) or (value.startswith("'") and value.endswith("'")):
        return value[1:-1]
    try:
        return int(value)
    except ValueError:
        return value


def read_front_matter(path: Path) -> dict[str, Any]:
    text = path.read_text(encoding="utf-8")
    match = FRONT_MATTER_RE.match(text)
    if not match:
        return {}
    meta: dict[str, Any] = {}
    for raw_line in match.group(1).splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#") or ":" not in line:
            continue
        key, value = line.split(":", 1)
        meta[key.strip()] = parse_scalar(value)
    return meta


def iter_records(records_dir: Path):
    for path in sorted(records_dir.glob("**/*.md")):
        if path.name.lower() == "readme.md":
            continue
        meta = read_front_matter(path)
        if meta:
            yield path, meta


def iso_week_range(week: str) -> tuple[dt.date, dt.date]:
    # week format: YYYY-Www, e.g. 2026-W16
    try:
        year_s, week_s = week.split("-W", 1)
        year = int(year_s)
        week_num = int(week_s)
    except Exception as exc:  # noqa: BLE001
        raise ValueError("Week must have format YYYY-Www, e.g. 2026-W16") from exc
    start = dt.date.fromisocalendar(year, week_num, 1)
    end = dt.date.fromisocalendar(year, week_num, 7)
    return start, end


def meta_date(meta: dict[str, Any]) -> dt.date | None:
    value = str(meta.get("date", "")).strip()
    if not value:
        return None
    try:
        return dt.date.fromisoformat(value)
    except ValueError:
        return None


def rel_link(from_file: Path, to_file: Path) -> str:
    return str(to_file.relative_to(from_file.parent).as_posix()) if to_file.is_relative_to(from_file.parent) else str(to_file.as_posix())
