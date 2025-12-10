
import argparse
import sys
import re
from pathlib import Path

import pandas as pd

# --------- Helpers ---------
def norm_col(s: str) -> str:
    s = str(s).strip()
    s = s.replace("（", "(").replace("）", ")")
    return s

def find_col(df, candidates, default=None):
    cols = {norm_col(c).lower(): c for c in df.columns}
    # also try stripped original names
    for c in df.columns:
        cols[c.strip().lower()] = c
    for cand in candidates:
        for k, orig in cols.items():
            if re.fullmatch(cand, k):
                return orig
    return default

def guess_preferences(df):
    # candidates: 志愿1, 志愿2, ..., Preference 1, 2, etc.
    pref_cols = []
    for c in df.columns:
        cl = norm_col(c).lower()
        if re.match(r'(志愿|意向|preference|prefer|志願)\s*[\d一二三四五六七八九十]+', cl):
            pref_cols.append(c)
    # Also accept columns that look like '1志愿' or '1st preference'
    if not pref_cols:
        for c in df.columns:
            cl = norm_col(c).lower()
            if re.match(r'[\d一二三四五六七八九十]+\s*(志愿|意向|preference|prefer|志願)', cl):
                pref_cols.append(c)
    # Fallback: columns named like site1/site2
    if not pref_cols:
        for c in df.columns:
            cl = norm_col(c).lower()
            if re.match(r'(site|赛站|站点|城市|region)[\s_]*\d+', cl):
                pref_cols.append(c)
    # Preserve original order
    return pref_cols

def load_excel(path):
    # Try to load sheets via pandas/openpyxl; if it fails due to style issues, raise a clear error.
    try:
        xls = pd.ExcelFile(path, engine="openpyxl")
        sheets = {name: pd.read_excel(xls, name) for name in xls.sheet_names}
        return sheets
    except Exception as e:
        raise RuntimeError(
            "无法读取Excel（可能是某些复杂样式导致）。请导出为 .xlsx（简单样式）或 .csv 再试，"
            "或者用 --teams-csv / --sites-csv 明确传入两个CSV文件。原始错误：%s" % (e,)
        )

def normalize_value(x):
    if pd.isna(x):
        return None
    s = str(x).strip()
    if not s:
        return None
    return s

def build_sites(df_sites):
    site_col = find_col(df_sites, [
        r'site', r'赛站', r'站点', r'城市', r'region', r'赛区'
    ])
    slots_col = find_col(df_sites, [
        r'slots?', r'名额', r'容量', r'配额', r'上限', r'人数上限'
    ])
    if not site_col or not slots_col:
        raise ValueError("无法在赛站表中识别赛站/名额列。请确保包含列：赛站/站点/城市 与 名额/slots。")
    sites = {}
    for _, row in df_sites.iterrows():
        name = normalize_value(row[site_col])
        if not name: 
            continue
        try:
            cap = int(row[slots_col])
        except Exception:
            continue
        sites[name] = cap
    if not sites:
        raise ValueError("赛站表解析为空。")
    return sites

def build_teams(df_teams):
    team_col = find_col(df_teams, [
        r'team', r'teamname', r'队伍', r'队名', r'用户名', r'学校队伍', r'队伍名称'
    ])
    order_col = find_col(df_teams, [
        r'(rank|order|priority|序号|顺序|名额顺序|排名)(\s*id)?'
    ])
    if not team_col or not order_col:
        raise ValueError("无法在志愿表中识别队伍或顺序列。请确保包含列：队伍/队名 与 顺序/名额顺序/rank。")
    pref_cols = guess_preferences(df_teams)
    if not pref_cols:
        raise ValueError("未找到志愿列（如 志愿1/志愿2 或 preference1/2 等）。")
    # Sort by order; allow numeric or mixed
    def safe_num(x):
        try:
            return float(x)
        except Exception:
            return float('inf')
    df_sorted = df_teams.copy()
    df_sorted["_order_key"] = df_sorted[order_col].apply(safe_num)
    df_sorted = df_sorted.sort_values(by=["_order_key", order_col], kind="mergesort")
    teams = []
    for _, row in df_sorted.iterrows():
        name = normalize_value(row[team_col])
        if not name:
            continue
        prefs = [normalize_value(row[c]) for c in pref_cols]
        prefs = [p for p in prefs if p]
        if not prefs:
            continue
        teams.append({"team": name, "order": row[order_col], "prefs": prefs})
    if not teams:
        raise ValueError("志愿表解析为空。")
    return teams, team_col, order_col, pref_cols

def allocate(teams, sites):
    remaining = dict(sites)
    assigned = []
    for t in teams:
        got = None
        pref_index = None
        for i, p in enumerate(t["prefs"], start=1):
            if p in remaining and remaining[p] > 0:
                remaining[p] -= 1
                got = p
                pref_index = i
                break
        assigned.append({
            "队伍": t["team"],
            "分配赛站": got if got else "",
            "匹配到第几志愿": pref_index if pref_index is not None else "",
        })
    return pd.DataFrame(assigned), remaining

def main():
    ap = argparse.ArgumentParser(description="ICPC 志愿表名额顺序分配脚本")
    ap.add_argument("input", nargs="?", help="包含赛站名额与队伍志愿的Excel文件（两个sheet）")
    ap.add_argument("--sites-sheet", default=None, help="Excel中赛站sheet名称，默认自动识别")
    ap.add_argument("--teams-sheet", default=None, help="Excel中队伍志愿sheet名称，默认自动识别")
    ap.add_argument("--sites-csv", default=None, help="直接传入赛站CSV路径（列：赛站/站点/城市, 名额/slots）")
    ap.add_argument("--teams-csv", default=None, help="直接传入志愿CSV路径（列：队伍/队名, 顺序/名额顺序, 志愿1/志愿2/...）")
    ap.add_argument("--team", default=None, help="只输出指定队伍（如 test_update_name）的分配结果")
    ap.add_argument("-o", "--output", default="allocation.csv", help="输出总表（CSV），默认 allocation.csv")
    args = ap.parse_args()

    if not args.input and not (args.sites_csv and args.teams_csv):
        print("请提供Excel文件，或 --sites-csv 与 --teams-csv。", file=sys.stderr)
        sys.exit(2)

    # Load sites
    if args.sites_csv:
        df_sites = pd.read_csv(args.sites_csv)
    else:
        sheets = load_excel(args.input)
        # pick sites sheet heuristically
        site_like = [k for k in sheets.keys() if re.search(r'(site|赛站|站点|城市|region|赛区|名额)', k, re.I)]
        if args.sites_sheet:
            site_sheet = args.sites_sheet
        else:
            site_sheet = site_like[0] if site_like else list(sheets.keys())[0]
        df_sites = sheets[site_sheet]

    # Load teams
    if args.teams_csv:
        df_teams = pd.read_csv(args.teams_csv)
    else:
        if 'sheets' not in locals():
            sheets = load_excel(args.input)
        team_like = [k for k in sheets.keys() if re.search(r'(志愿|队伍|team|preference)', k, re.I)]
        if args.teams_sheet:
            team_sheet = args.teams_sheet
        else:
            # Prefer a different sheet than sites if possible
            candidates = [k for k in team_like if k != site_sheet] if 'site_sheet' in locals() else team_like
            team_sheet = candidates[0] if candidates else list(sheets.keys())[0]
        df_teams = sheets[team_sheet]

    sites = build_sites(df_sites)
    teams, team_col, order_col, pref_cols = build_teams(df_teams)
    result_df, remaining = allocate(teams, sites)

    # Save output
    out_path = Path(args.output)
    result_df.to_csv(out_path, index=False, encoding="utf-8-sig")

    if args.team:
        row = result_df[result_df["队伍"].str.lower() == args.team.lower()]
        if not row.empty:
            rec = row.iloc[0].to_dict()
            print(f"{rec['队伍']} -> 分配赛站: {rec['分配赛站'] or '未分配'} "
                  f"(匹配到第{rec['匹配到第几志愿']}志愿)" )
        else:
            print(f"未找到队伍：{args.team}")

    # Also print remaining seats summary
    print("\n剩余名额：")
    for k, v in remaining.items():
        print(f"{k}: {v}")

    print(f"\n已写出结果: {out_path}")

if __name__ == "__main__":
    main()
