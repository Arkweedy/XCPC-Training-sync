#!/usr/bin/env python3
# stress.py - WSL/Linux stress tester for mycode.cpp vs std.cpp with gen.cpp
#
# v3 changes:
# - Python 3.10 compatible (no illegal f-string backslash expressions)
# - Optional gdb backtrace on signal RE ( --bt ) to obtain file:line for /0, segfault, etc.
# - gen.err not kept for successful rounds; only saved when GEN fails
# - case naming: 2-digit display id + TAG + timestamp; no WA_WA duplication
# - commands: run / repro / clean / cases (list|retest|clear)

import argparse
import json
import os
import re
import shutil
import signal
import subprocess
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Optional, Tuple, List, Dict

TOOL_DIR = Path(".stress")
BUILD_DIR = TOOL_DIR / "build"
TMP_DIR = TOOL_DIR / "tmp"
CASES_DIR = TOOL_DIR / "cases"
LAST_DIR = TOOL_DIR / "last"
SEQ_FILE = TOOL_DIR / "seq.txt"

SRC_MY = Path("mycode.cpp")
SRC_STD = Path("std.cpp")
SRC_GEN = Path("gen.cpp")

EXE_MY = BUILD_DIR / "mycode"
EXE_STD = BUILD_DIR / "std"
EXE_GEN = BUILD_DIR / "gen"

AC, WA, CE, RE_, TLE, MLE = "AC", "WA", "CE", "RE", "TLE", "MLE"

CPP_LINE_PAT = re.compile(r"(?P<file>[^:\s]+\.cpp):(?P<line>\d+)(?::(?P<col>\d+))?")

# loader / OOM hints under memory limit
MLE_HINT_PATTERNS = [
    r"std::bad_alloc",
    r"bad alloc",
    r"out of memory",
    r"cannot allocate memory",
    r"AddressSanitizer: out of memory",
    r"failed to map segment from shared object",
    r"error while loading shared libraries",
    r"failed to map segment",
]

ANSI = {
    "reset": "\033[0m",
    "red": "\033[31m",
    "green": "\033[32m",
    "yellow": "\033[33m",
    "magenta": "\033[35m",
    "cyan": "\033[36m",
    "gray": "\033[90m",
}

def use_color() -> bool:
    return sys.stdout.isatty() and os.environ.get("NO_COLOR") is None

def colorize(s: str, c: str) -> str:
    if not use_color():
        return s
    return f"{ANSI.get(c,'')}{s}{ANSI['reset']}"

def status_color(st: str) -> str:
    if st == AC:
        return "green"
    if st == WA:
        return "red"
    if st == CE:
        return "red"
    if st == RE_:
        return "red"
    if st == TLE:
        return "yellow"
    if st == MLE:
        return "magenta"
    return "cyan"

def now_stamp() -> str:
    return time.strftime("%Y%m%d_%H%M%S", time.localtime())

def ensure_dirs():
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    TMP_DIR.mkdir(parents=True, exist_ok=True)
    CASES_DIR.mkdir(parents=True, exist_ok=True)
    LAST_DIR.mkdir(parents=True, exist_ok=True)

def write_text(p: Path, s: str):
    p.parent.mkdir(parents=True, exist_ok=True)
    p.write_text(s, encoding="utf-8", errors="replace")

def read_text_safe(p: Path, max_bytes: int = 2_000_000) -> str:
    try:
        data = p.read_bytes()
        if len(data) > max_bytes:
            data = data[:max_bytes] + b"\n\n[... truncated ...]\n"
        return data.decode(errors="replace")
    except FileNotFoundError:
        return ""
    except Exception as e:
        return f"[read error: {e}]"

def ensure_sources_exist() -> Tuple[bool, str]:
    missing = [p.name for p in (SRC_MY, SRC_STD, SRC_GEN) if not p.exists()]
    if missing:
        return False, f"missing source files: {', '.join(missing)} (need mycode.cpp/std.cpp/gen.cpp)"
    return True, ""

def load_seq() -> int:
    try:
        return int(SEQ_FILE.read_text().strip())
    except Exception:
        return 0

def next_case_id() -> int:
    ensure_dirs()
    x = load_seq() + 1
    write_text(SEQ_FILE, str(x))
    return x

def reset_seq():
    ensure_dirs()
    write_text(SEQ_FILE, "0")

def disp_id2(n: int) -> str:
    # always 2 digits for display; meta keeps full seq id
    return f"{(n % 100):02d}"

def progress_step(r: int) -> int:
    if r <= 100:
        return 1
    if r <= 1000:
        return 10
    return 100

@dataclass
class RunResult:
    status: str
    returncode: Optional[int]
    signum: Optional[int]
    duration_ms: int
    mle_hint: bool
    re_location: Optional[str]

def _preexec_set_limits(ml_mb: Optional[int]):
    os.setsid()
    if ml_mb is None:
        return
    try:
        import resource
        lim = int(ml_mb) * 1024 * 1024
        resource.setrlimit(resource.RLIMIT_AS, (lim, lim))
        try:
            resource.setrlimit(resource.RLIMIT_DATA, (lim, lim))
        except Exception:
            pass
    except Exception:
        pass

def parse_location(stderr_text: str, prefer_cpp: Optional[str]) -> Optional[str]:
    found_any = None
    for m in CPP_LINE_PAT.finditer(stderr_text):
        f = m.group("file")
        loc = f"{f}:{m.group('line')}"
        if found_any is None:
            found_any = loc
        if prefer_cpp and f.endswith(prefer_cpp):
            return loc
    return found_any

def run_program(
    exe: Path,
    stdin_path: Optional[Path],
    stdout_path: Path,
    stderr_path: Path,
    tl_sec: float,
    ml_mb: Optional[int],
    prefer_cpp: Optional[str],
) -> RunResult:
    start = time.perf_counter()
    stdout_path.parent.mkdir(parents=True, exist_ok=True)
    stderr_path.parent.mkdir(parents=True, exist_ok=True)

    with open(stdout_path, "wb") as fo, open(stderr_path, "wb") as fe:
        fin = None
        try:
            if stdin_path is not None:
                fin = open(stdin_path, "rb")

            p = subprocess.Popen(
                [str(exe)],
                stdin=fin,
                stdout=fo,
                stderr=fe,
                preexec_fn=lambda: _preexec_set_limits(ml_mb),
            )

            try:
                p.wait(timeout=tl_sec)
                timed_out = False
            except subprocess.TimeoutExpired:
                timed_out = True
                try:
                    os.killpg(p.pid, signal.SIGKILL)
                except Exception:
                    try:
                        p.kill()
                    except Exception:
                        pass

            end = time.perf_counter()
            dur_ms = int((end - start) * 1000)

            if timed_out:
                return RunResult(TLE, p.returncode, None, dur_ms, False, None)

            rc = p.returncode
            signum = None
            if rc is not None and rc < 0:
                signum = -rc

            if rc == 0:
                return RunResult(AC, rc, signum, dur_ms, False, None)

            err_text = read_text_safe(stderr_path, max_bytes=500_000)
            mle_hint = False
            if ml_mb is not None:
                mle_hint = any(re.search(pat, err_text, re.IGNORECASE) for pat in MLE_HINT_PATTERNS)

            loc = parse_location(err_text, prefer_cpp)

            if ml_mb is not None:
                if signum == signal.SIGKILL:
                    return RunResult(MLE, rc, signum, dur_ms, mle_hint, loc)
                if mle_hint:
                    return RunResult(MLE, rc, signum, dur_ms, mle_hint, loc)

            return RunResult(RE_, rc, signum, dur_ms, mle_hint, loc)

        except FileNotFoundError:
            end = time.perf_counter()
            dur_ms = int((end - start) * 1000)
            return RunResult(RE_, None, None, dur_ms, False, None)
        finally:
            try:
                if fin is not None:
                    fin.close()
            except Exception:
                pass

def compile_cpp(src: Path, out: Path, mode: str, extra: List[str]) -> Tuple[bool, str, List[str]]:
    flags = ["-std=c++20"]
    if mode == "debug":
        flags += ["-O0", "-g", "-fno-omit-frame-pointer", "-fsanitize=address,undefined"]
    else:
        flags += ["-O2", "-pipe"]
    flags += extra
    cmd = ["g++", str(src)] + flags + ["-o", str(out)]
    proc = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    ok = (proc.returncode == 0)
    return ok, proc.stdout, cmd

def tail(s: str, n: int = 120000) -> str:
    return s[-n:] if len(s) > n else s

def gdb_backtrace(exe: Path, input_path: Path, timeout_sec: float) -> Tuple[Optional[str], str]:
    """
    Run gdb in batch mode and return:
      (best_location, full_bt_text)
    best_location tries to find 'at mycode.cpp:LINE' in backtrace.
    """
    # gdb -q -batch --args ./mycode
    #   -ex "set pagination off"
    #   -ex "run < input.txt"
    #   -ex "bt"
    cmd = [
        "gdb", "-q", "-batch",
        "-ex", "set pagination off",
        "-ex", f"run < {str(input_path)}",
        "-ex", "bt",
        "--args", str(exe)
    ]
    try:
        p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, timeout=timeout_sec)
        out = p.stdout
    except FileNotFoundError:
        return None, "gdb not found. Install with: sudo apt-get install gdb\n"
    except subprocess.TimeoutExpired:
        return None, "gdb backtrace timeout\n"

    # find first frame containing ' at xxx.cpp:line'
    loc = None
    m = re.search(r"\bat\s+([^\s:]+\.cpp):(\d+)\b", out)
    if m:
        loc = f"{m.group(1)}:{m.group(2)}"
    return loc, out

def update_last(state: Dict, files: Dict[str, Path], note: Optional[str] = None):
    ensure_dirs()
    data = dict(state)
    if note:
        data["note"] = note
    write_text(LAST_DIR / "status.json", json.dumps(data, ensure_ascii=False, indent=2))
    for name, src in files.items():
        dst = LAST_DIR / name
        try:
            if src.exists():
                shutil.copyfile(src, dst)
            else:
                write_text(dst, "[missing]")
        except Exception as e:
            write_text(dst, f"[copy error: {e}]")

def save_case(
    tag: str,                 # e.g. WA / MY_RE / STD_TLE / GEN_MLE / CE_STD
    debug: bool,
    chk: bool,
    bt: bool,
    tl: float,
    ml: Optional[int],
    ml_gen: Optional[int],
    compile_cmds: dict,
    compile_logs: dict,
    run_meta: dict,
    report: str,
    tmp_files: Dict[str, Path],
) -> Path:
    cid = next_case_id()
    case_name = f"{disp_id2(cid)}_{tag}_{now_stamp()}"
    case_dir = CASES_DIR / case_name
    case_dir.mkdir(parents=True, exist_ok=True)

    for name, src in tmp_files.items():
        dst = case_dir / name
        try:
            if src.exists():
                shutil.copyfile(src, dst)
            else:
                write_text(dst, "[missing]")
        except Exception as e:
            write_text(dst, f"[copy error: {e}]")

    meta = {
        "seq_id": cid,
        "display_id": disp_id2(cid),
        "tag": tag,
        "debug": debug,
        "chk": chk,
        "bt": bt,
        "tl_sec": tl,
        "ml_mb": ml,
        "ml_gen_mb": ml_gen,
        "compile_cmds": compile_cmds,
        "compile_logs_tail": {k: v[-4000:] for k, v in compile_logs.items()},
        "run_meta": run_meta,
        "created_at": now_stamp(),
    }
    write_text(case_dir / "report.txt", report)
    write_text(case_dir / "meta.json", json.dumps(meta, ensure_ascii=False, indent=2))
    return case_dir

def do_clean():
    ensure_dirs()
    shutil.rmtree(TMP_DIR, ignore_errors=True)
    shutil.rmtree(BUILD_DIR, ignore_errors=True)
    shutil.rmtree(LAST_DIR, ignore_errors=True)
    TMP_DIR.mkdir(parents=True, exist_ok=True)
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    LAST_DIR.mkdir(parents=True, exist_ok=True)
    reset_seq()
    print("cleaned .stress/tmp .stress/build .stress/last and reset case id (kept .stress/cases)")

def do_cases_list():
    ensure_dirs()
    items = sorted([p for p in CASES_DIR.iterdir() if p.is_dir()], key=lambda x: x.name)
    if not items:
        print("no cases.")
        return
    for p in items:
        print(p)

def do_cases_clear(yes: bool):
    ensure_dirs()
    if not yes:
        print("Refusing to clear cases without --yes")
        return
    shutil.rmtree(CASES_DIR, ignore_errors=True)
    CASES_DIR.mkdir(parents=True, exist_ok=True)
    print("cleared .stress/cases")

def compile_all(debug: bool, chk: bool, bt: bool) -> Tuple[bool, dict, dict]:
    """
    - debug: sanitizer mode (-g -fsanitize=...)
    - chk: mycode uses libstdc++ debug checks (may turn many WA into RE)
    - bt: enable gdb backtrace on RE without location => must compile with -g and keep frame pointers
    """
    compile_cmds = {}
    compile_logs = {}

    gen_mode = "debug" if debug else "release"
    std_mode = "debug" if debug else "release"
    my_mode = "debug" if (debug or chk) else "release"

    extra_std: List[str] = []
    extra_my: List[str] = []

    if chk:
        extra_my += ["-D_GLIBCXX_DEBUG", "-D_GLIBCXX_DEBUG_PEDANTIC", "-D_GLIBCXX_ASSERTIONS"]

    # if we may need gdb, ensure debug symbols exist (at least for std/mycode)
    if bt and not debug:
        extra_std += ["-g", "-fno-omit-frame-pointer"]
        extra_my += ["-g", "-fno-omit-frame-pointer"]

    ok, log, cmd = compile_cpp(SRC_GEN, EXE_GEN, gen_mode, [])
    compile_cmds["gen"] = cmd
    compile_logs["gen"] = log
    if not ok:
        return False, compile_cmds, compile_logs

    ok, log, cmd = compile_cpp(SRC_STD, EXE_STD, std_mode, extra_std)
    compile_cmds["std"] = cmd
    compile_logs["std"] = log
    if not ok:
        return False, compile_cmds, compile_logs

    ok, log, cmd = compile_cpp(SRC_MY, EXE_MY, my_mode, extra_my)
    compile_cmds["mycode"] = cmd
    compile_logs["mycode"] = log
    if not ok:
        return False, compile_cmds, compile_logs

    return True, compile_cmds, compile_logs

# --- diff (token-based) ---
@dataclass
class Tok:
    s: str
    line: int
    col: int

def tokenize_with_pos(text: str) -> List[Tok]:
    tokens: List[Tok] = []
    in_tok = False
    buf = []
    line, col = 1, 1
    tok_line, tok_col = 1, 1

    for ch in text:
        if ch.isspace():
            if in_tok:
                tokens.append(Tok("".join(buf), tok_line, tok_col))
                buf.clear()
                in_tok = False
            if ch == "\n":
                line += 1
                col = 1
            else:
                col += 1
        else:
            if not in_tok:
                in_tok = True
                tok_line, tok_col = line, col
            buf.append(ch)
            col += 1

    if in_tok:
        tokens.append(Tok("".join(buf), tok_line, tok_col))
    return tokens

def shorten_context(xs: List[str], max_chars: int = 240) -> str:
    s = " ".join(xs)
    if len(s) <= max_chars:
        return s
    return s[:max_chars] + " ..."

def diff_outputs(std_out: Path, my_out: Path) -> str:
    try:
        sz1 = std_out.stat().st_size
        sz2 = my_out.stat().st_size
    except FileNotFoundError:
        return "diff: output file missing"

    if (sz1 > 8_000_000) or (sz2 > 8_000_000):
        return diff_outputs_line(std_out, my_out)

    a = read_text_safe(std_out, max_bytes=10_000_000)
    b = read_text_safe(my_out, max_bytes=10_000_000)

    ta = tokenize_with_pos(a)
    tb = tokenize_with_pos(b)

    n = min(len(ta), len(tb))
    for i in range(n):
        if ta[i].s != tb[i].s:
            lctx_a = [t.s for t in ta[max(0, i - 10): i + 11]]
            lctx_b = [t.s for t in tb[max(0, i - 10): i + 11]]
            return (
                f"WA at token #{i+1}\n"
                f"std: (line {ta[i].line}, col {ta[i].col}) {ta[i].s!r}\n"
                f"my : (line {tb[i].line}, col {tb[i].col}) {tb[i].s!r}\n"
                f"context std: {shorten_context(lctx_a)}\n"
                f"context my : {shorten_context(lctx_b)}\n"
            )

    if len(ta) != len(tb):
        if len(ta) < len(tb):
            extra = tb[len(ta)]
            ctx = [t.s for t in tb[max(0, len(ta) - 5): min(len(tb), len(ta) + 10)]]
            return (
                f"WA: std output ended early at token #{len(ta)+1}\n"
                f"my first extra token: (line {extra.line}, col {extra.col}) {extra.s!r}\n"
                f"context my : {shorten_context(ctx)}\n"
            )
        else:
            extra = ta[len(tb)]
            ctx = [t.s for t in ta[max(0, len(tb) - 5): min(len(ta), len(tb) + 10)]]
            return (
                f"WA: my output ended early at token #{len(tb)+1}\n"
                f"std first extra token: (line {extra.line}, col {extra.col}) {extra.s!r}\n"
                f"context std: {shorten_context(ctx)}\n"
            )

    return "No diff found under tokenization (unexpected)."

def diff_outputs_line(std_out: Path, my_out: Path) -> str:
    def safe_open(p: Path):
        return open(p, "r", encoding="utf-8", errors="replace", newline="")

    pre: List[str] = []
    line_no = 0
    with safe_open(std_out) as fa, safe_open(my_out) as fb:
        while True:
            la = fa.readline()
            lb = fb.readline()
            if not la and not lb:
                return "No diff found (line-based)."
            line_no += 1
            if la != lb:
                after_a = [fa.readline() for _ in range(2)]
                after_b = [fb.readline() for _ in range(2)]
                def fmt(lines: List[str]) -> str:
                    return "".join(lines).rstrip("\n")
                return (
                    f"WA at line {line_no}\n"
                    f"--- std (context) ---\n{fmt(pre + [la] + after_a)}\n"
                    f"--- my  (context) ---\n{fmt(pre + [lb] + after_b)}\n"
                )
            pre.append(la)
            if len(pre) > 2:
                pre.pop(0)

def do_run(n: int, tl: float, ml: Optional[int], ml_gen: Optional[int], debug: bool, chk: bool, bt: bool):
    ok, msg = ensure_sources_exist()
    if not ok:
        print(msg)
        sys.exit(2)

    ensure_dirs()
    okc, compile_cmds, compile_logs = compile_all(debug, chk, bt)
    if not okc:
        report = f"{CE}: compile failed\n"
        for k, lg in compile_logs.items():
            if lg and "error:" in lg:
                report += f"\n--- {k} compiler output (tail) ---\n{lg[-4000:]}\n"
        tmp_files = {}
        case_dir = save_case(
            tag="CE",
            debug=debug, chk=chk, bt=bt, tl=tl, ml=ml, ml_gen=ml_gen,
            compile_cmds=compile_cmds, compile_logs=compile_logs,
            run_meta={}, report=report, tmp_files=tmp_files
        )
        print(report)
        print(f"saved to: {case_dir}")
        sys.exit(1)

    print(
        f"compiled OK. mode={'debug' if debug else 'release'}"
        f"{' +chk(mycode)' if chk else ''}"
        f"{' +bt(gdb)' if bt else ''}, "
        f"tl={tl}s, ml(std/my)={ml if ml is not None else '∞'}MB, ml(gen)={ml_gen if ml_gen is not None else '∞'}MB"
    )
    print("progress: 1..100 per1, 101..1000 per10, 1001+ per100")
    print(f"running up to {n} rounds, stop on first non-AC...")

    tmp_input = TMP_DIR / "input.txt"
    tmp_std_out = TMP_DIR / "std.out"
    tmp_std_err = TMP_DIR / "std.err"
    tmp_my_out = TMP_DIR / "my.out"
    tmp_my_err = TMP_DIR / "my.err"
    tmp_gen_err = TMP_DIR / "gen.err"
    tmp_my_bt = TMP_DIR / "my.bt.txt"

    cnt_ac = 0

    for r in range(1, n + 1):
        for p in [tmp_input, tmp_std_out, tmp_std_err, tmp_my_out, tmp_my_err, tmp_gen_err, tmp_my_bt]:
            try:
                p.unlink()
            except FileNotFoundError:
                pass

        # GEN: keep gen.err only when gen fails (still captured to allow diagnosing)
        gen_res = run_program(EXE_GEN, None, tmp_input, tmp_gen_err, tl_sec=tl, ml_mb=ml_gen, prefer_cpp="gen.cpp")
        if gen_res.status != AC:
            loc_line = f"location: {gen_res.re_location}\n" if gen_res.re_location else ""
            report = (
                f"GEN {gen_res.status}\n"
                f"gen: rc={gen_res.returncode}, sig={gen_res.signum}, {gen_res.duration_ms}ms\n"
                f"{loc_line}"
                f"stderr (tail):\n{tail(read_text_safe(tmp_gen_err, 300_000), 120000)}\n"
            )
            run_meta = {"gen": gen_res.__dict__}
            tmp_files = {"input.txt": tmp_input, "gen.err": tmp_gen_err}
            case_dir = save_case(
                tag=f"GEN_{gen_res.status}",
                debug=debug, chk=chk, bt=bt, tl=tl, ml=ml, ml_gen=ml_gen,
                compile_cmds=compile_cmds, compile_logs=compile_logs,
                run_meta=run_meta, report=report, tmp_files=tmp_files
            )
            update_last(
                state={"round": r, "result": f"GEN_{gen_res.status}", "case_dir": str(case_dir)},
                files={"input.txt": tmp_input, "gen.err": tmp_gen_err},
                note="generator failed"
            )
            print(f"[{r}] " + colorize("GEN " + gen_res.status, status_color(gen_res.status)) + f"  (saved: {case_dir})")
            print(report)
            print(f"repro: python3 stress.py repro {case_dir}")
            return

        std_res = run_program(EXE_STD, tmp_input, tmp_std_out, tmp_std_err, tl_sec=tl, ml_mb=ml, prefer_cpp="std.cpp")
        if std_res.status != AC:
            loc_line = f"location: {std_res.re_location}\n" if std_res.re_location else ""
            report = (
                f"STD {std_res.status}\n"
                f"std: rc={std_res.returncode}, sig={std_res.signum}, {std_res.duration_ms}ms\n"
                f"{loc_line}"
                f"stderr (tail):\n{tail(read_text_safe(tmp_std_err, 300_000), 120000)}\n"
            )
            run_meta = {"std": std_res.__dict__}
            tmp_files = {"input.txt": tmp_input, "std.out": tmp_std_out, "std.err": tmp_std_err}
            case_dir = save_case(
                tag=f"STD_{std_res.status}",
                debug=debug, chk=chk, bt=bt, tl=tl, ml=ml, ml_gen=ml_gen,
                compile_cmds=compile_cmds, compile_logs=compile_logs,
                run_meta=run_meta, report=report, tmp_files=tmp_files
            )
            update_last(
                state={"round": r, "result": f"STD_{std_res.status}", "case_dir": str(case_dir)},
                files={"input.txt": tmp_input, "std.out": tmp_std_out, "std.err": tmp_std_err},
                note="std failed"
            )
            print(f"[{r}] " + colorize("STD " + std_res.status, status_color(std_res.status)) + f"  (saved: {case_dir})")
            print(report)
            print(f"repro: python3 stress.py repro {case_dir}")
            return

        my_res = run_program(EXE_MY, tmp_input, tmp_my_out, tmp_my_err, tl_sec=tl, ml_mb=ml, prefer_cpp="mycode.cpp")
        if my_res.status != AC:
            err_text = read_text_safe(tmp_my_err, 500_000)
            loc = parse_location(err_text, "mycode.cpp")

            bt_loc = None
            bt_text = ""
            # If signal-type crash without location, optionally run gdb backtrace
            if bt and (loc is None) and (my_res.signum is not None):
                bt_loc, bt_text = gdb_backtrace(EXE_MY, tmp_input, timeout_sec=max(5.0, tl * 5.0))
                if bt_text:
                    write_text(tmp_my_bt, bt_text)
                if loc is None and bt_loc is not None:
                    loc = bt_loc

            loc_line = f"location: {loc}\n" if loc else ""
            bt_note = ""
            if bt and bt_text:
                bt_note = "gdb backtrace saved: my.bt.txt\n"

            report = (
                f"MYCODE {my_res.status}\n"
                f"my: rc={my_res.returncode}, sig={my_res.signum}, {my_res.duration_ms}ms\n"
                f"{loc_line}"
                f"{bt_note}"
                f"stderr (tail):\n{tail(err_text, 160000)}\n"
            )
            run_meta = {"std": std_res.__dict__, "my": my_res.__dict__}
            tmp_files = {
                "input.txt": tmp_input,
                "std.out": tmp_std_out,
                "std.err": tmp_std_err,
                "my.out": tmp_my_out,
                "my.err": tmp_my_err,
            }
            if bt and tmp_my_bt.exists():
                tmp_files["my.bt.txt"] = tmp_my_bt

            case_dir = save_case(
                tag=f"MY_{my_res.status}",
                debug=debug, chk=chk, bt=bt, tl=tl, ml=ml, ml_gen=ml_gen,
                compile_cmds=compile_cmds, compile_logs=compile_logs,
                run_meta=run_meta, report=report, tmp_files=tmp_files
            )
            update_last(
                state={"round": r, "result": f"MY_{my_res.status}", "case_dir": str(case_dir)},
                files=tmp_files,
                note="mycode failed"
            )
            print(f"[{r}] " + colorize("MY " + my_res.status, status_color(my_res.status)) + f"  (saved: {case_dir})")
            print(report)
            print(f"repro: python3 stress.py repro {case_dir}" + (" --bt" if bt else ""))
            return

        # compare outputs
        try:
            same = tmp_std_out.read_bytes() == tmp_my_out.read_bytes()
        except Exception:
            same = False

        if not same:
            d = diff_outputs(tmp_std_out, tmp_my_out)
            report = (
                f"{WA}\n"
                f"round={r}\n"
                f"std_time={std_res.duration_ms}ms, my_time={my_res.duration_ms}ms\n\n"
                f"{d}\n"
            )
            run_meta = {"std": std_res.__dict__, "my": my_res.__dict__}
            tmp_files = {
                "input.txt": tmp_input,
                "std.out": tmp_std_out,
                "std.err": tmp_std_err,
                "my.out": tmp_my_out,
                "my.err": tmp_my_err,
            }
            case_dir = save_case(
                tag="WA",
                debug=debug, chk=chk, bt=bt, tl=tl, ml=ml, ml_gen=ml_gen,
                compile_cmds=compile_cmds, compile_logs=compile_logs,
                run_meta=run_meta, report=report, tmp_files=tmp_files
            )
            update_last(
                state={"round": r, "result": WA, "case_dir": str(case_dir)},
                files=tmp_files,
                note="outputs differ"
            )
            print(f"[{r}] " + colorize(WA, status_color(WA)) + f"  (saved: {case_dir})")
            print(report)
            print(f"repro: python3 stress.py repro {case_dir}")
            return

        cnt_ac += 1
        step = progress_step(r)
        if (r <= 100) or (r % step == 0):
            msg = f"[{r}] {AC}  (std {std_res.duration_ms}ms, my {my_res.duration_ms}ms, AC={cnt_ac})"
            print(colorize(msg, status_color(AC)))

    update_last(
        state={"round": n, "result": AC, "note": f"finished {n} rounds"},
        files={"input.txt": tmp_input, "std.out": tmp_std_out, "std.err": tmp_std_err,
               "my.out": tmp_my_out, "my.err": tmp_my_err},
        note="finished all rounds"
    )
    print(colorize(f"All {n} rounds: {AC}", status_color(AC)))

def do_repro(case_dir: Path, tl: float, ml: Optional[int], debug: bool, chk: bool, bt: bool):
    case_dir = case_dir.resolve()
    if not case_dir.exists():
        print(f"case dir not found: {case_dir}")
        sys.exit(2)

    input_path = case_dir / "input.txt"
    if not input_path.exists():
        print(f"input.txt not found in: {case_dir}")
        sys.exit(2)

    ensure_dirs()

    # compile std + mycode only
    compile_cmds = {}
    compile_logs = {}

    std_mode = "debug" if debug else "release"
    my_mode = "debug" if (debug or chk) else "release"
    extra_std: List[str] = []
    extra_my: List[str] = []

    if chk:
        extra_my += ["-D_GLIBCXX_DEBUG", "-D_GLIBCXX_DEBUG_PEDANTIC", "-D_GLIBCXX_ASSERTIONS"]
    if bt and not debug:
        extra_std += ["-g", "-fno-omit-frame-pointer"]
        extra_my += ["-g", "-fno-omit-frame-pointer"]

    okc, log, cmd = compile_cpp(SRC_STD, EXE_STD, std_mode, extra_std)
    compile_cmds["std"] = cmd
    compile_logs["std"] = log
    if not okc:
        print(colorize("CE: compile failed for std", "red"))
        print(log[-4000:])
        return

    okc, log, cmd = compile_cpp(SRC_MY, EXE_MY, my_mode, extra_my)
    compile_cmds["mycode"] = cmd
    compile_logs["mycode"] = log
    if not okc:
        print(colorize("CE: compile failed for mycode", "red"))
        print(log[-4000:])
        return

    tmp_std_out = TMP_DIR / "repro_std.out"
    tmp_std_err = TMP_DIR / "repro_std.err"
    tmp_my_out = TMP_DIR / "repro_my.out"
    tmp_my_err = TMP_DIR / "repro_my.err"
    tmp_my_bt = TMP_DIR / "repro_my.bt.txt"

    for p in [tmp_std_out, tmp_std_err, tmp_my_out, tmp_my_err, tmp_my_bt]:
        try:
            p.unlink()
        except FileNotFoundError:
            pass

    std_res = run_program(EXE_STD, input_path, tmp_std_out, tmp_std_err, tl_sec=tl, ml_mb=ml, prefer_cpp="std.cpp")
    my_res = run_program(EXE_MY, input_path, tmp_my_out, tmp_my_err, tl_sec=tl, ml_mb=ml, prefer_cpp="mycode.cpp")

    print(colorize(f"repro case: {case_dir}", "cyan"))
    print(f"STD: " + colorize(std_res.status, status_color(std_res.status)) + f" ({std_res.duration_ms}ms, rc={std_res.returncode}, sig={std_res.signum})")
    if std_res.status != AC:
        print(tail(read_text_safe(tmp_std_err, 300_000), 200000))
        return

    print(f"MY : " + colorize(my_res.status, status_color(my_res.status)) + f" ({my_res.duration_ms}ms, rc={my_res.returncode}, sig={my_res.signum})")
    if my_res.status != AC:
        err_text = read_text_safe(tmp_my_err, 500_000)
        loc = parse_location(err_text, "mycode.cpp")
        if bt and (loc is None) and (my_res.signum is not None):
            bt_loc, bt_text = gdb_backtrace(EXE_MY, input_path, timeout_sec=max(5.0, tl * 5.0))
            if bt_text:
                write_text(tmp_my_bt, bt_text)
                print(colorize("gdb backtrace saved: repro_my.bt.txt", "gray"))
            if loc is None and bt_loc is not None:
                loc = bt_loc
        if loc:
            print("location:", colorize(loc, "yellow"))
        print(tail(err_text, 200000))
        # save repro outputs into case dir
        shutil.copyfile(tmp_std_out, case_dir / "repro_std.out")
        shutil.copyfile(tmp_std_err, case_dir / "repro_std.err")
        shutil.copyfile(tmp_my_out, case_dir / "repro_my.out")
        shutil.copyfile(tmp_my_err, case_dir / "repro_my.err")
        if tmp_my_bt.exists():
            shutil.copyfile(tmp_my_bt, case_dir / "repro_my.bt.txt")
        print(colorize("saved repro outputs into case dir.", "gray"))
        return

    try:
        same = tmp_std_out.read_bytes() == tmp_my_out.read_bytes()
    except Exception:
        same = False

    if same:
        print(colorize("COMPARE: AC (outputs identical)", "green"))
    else:
        d = diff_outputs(tmp_std_out, tmp_my_out)
        print(colorize("COMPARE: WA", "red"))
        print(d)
        shutil.copyfile(tmp_std_out, case_dir / "repro_std.out")
        shutil.copyfile(tmp_std_err, case_dir / "repro_std.err")
        shutil.copyfile(tmp_my_out, case_dir / "repro_my.out")
        shutil.copyfile(tmp_my_err, case_dir / "repro_my.err")
        write_text(case_dir / "repro_report.txt", d)
        print(colorize("saved repro outputs + repro_report.txt into case dir.", "gray"))

def do_cases_retest(tl: float, ml: Optional[int], debug: bool, chk: bool, bt: bool):
    ensure_dirs()
    items = sorted([p for p in CASES_DIR.iterdir() if p.is_dir()], key=lambda x: x.name)
    if not items:
        print("no cases to retest.")
        return

    std_mode = "debug" if debug else "release"
    my_mode = "debug" if (debug or chk) else "release"
    extra_std: List[str] = []
    extra_my: List[str] = []
    if chk:
        extra_my += ["-D_GLIBCXX_DEBUG", "-D_GLIBCXX_DEBUG_PEDANTIC", "-D_GLIBCXX_ASSERTIONS"]
    if bt and not debug:
        extra_std += ["-g", "-fno-omit-frame-pointer"]
        extra_my += ["-g", "-fno-omit-frame-pointer"]

    okc, log, _ = compile_cpp(SRC_STD, EXE_STD, std_mode, extra_std)
    if not okc:
        print(colorize("CE: compile failed for std", "red"))
        print(log[-4000:])
        return
    okc, log, _ = compile_cpp(SRC_MY, EXE_MY, my_mode, extra_my)
    if not okc:
        print(colorize("CE: compile failed for mycode", "red"))
        print(log[-4000:])
        return

    passed = 0
    failed = 0

    for case in items:
        inp = case / "input.txt"
        if not inp.exists():
            print(case.name, colorize("SKIP(no input.txt)", "yellow"))
            continue

        tmp_std_out = TMP_DIR / "retest_std.out"
        tmp_std_err = TMP_DIR / "retest_std.err"
        tmp_my_out = TMP_DIR / "retest_my.out"
        tmp_my_err = TMP_DIR / "retest_my.err"
        for p in [tmp_std_out, tmp_std_err, tmp_my_out, tmp_my_err]:
            try:
                p.unlink()
            except FileNotFoundError:
                pass

        std_res = run_program(EXE_STD, inp, tmp_std_out, tmp_std_err, tl_sec=tl, ml_mb=ml, prefer_cpp="std.cpp")
        my_res = run_program(EXE_MY, inp, tmp_my_out, tmp_my_err, tl_sec=tl, ml_mb=ml, prefer_cpp="mycode.cpp")

        if std_res.status != AC:
            final = "STD_" + std_res.status
        elif my_res.status != AC:
            final = "MY_" + my_res.status
        else:
            try:
                same = tmp_std_out.read_bytes() == tmp_my_out.read_bytes()
            except Exception:
                same = False
            final = AC if same else WA

        if final == AC:
            passed += 1
        else:
            failed += 1

        st = final.split("_")[-1] if "_" in final else final
        print(case.name, colorize(final, status_color(st)))

    print(colorize(f"retest done: AC={passed}, non-AC={failed}", "cyan"))

def main():
    parser = argparse.ArgumentParser(description="WSL stress tool: mycode.cpp vs std.cpp with gen.cpp")
    sub = parser.add_subparsers(dest="cmd", required=True)

    p_run = sub.add_parser("run", help="compile then stress test until failure")
    p_run.add_argument("-n", type=int, default=10000)
    p_run.add_argument("--tl", type=float, default=5.0)
    p_run.add_argument("--ml", type=int, default=None, help="memory limit MB (std & mycode)")
    p_run.add_argument("--ml-gen", type=int, default=None, help="memory limit MB for gen (default: no limit)")
    p_run.add_argument("--debug", action="store_true", help="sanitizer build (-fsanitize=address,undefined -g)")
    p_run.add_argument("--chk", action="store_true", help="mycode with libstdc++ debug checks")
    p_run.add_argument("--bt", action="store_true", help="on signal RE without location, run gdb backtrace")

    p_repro = sub.add_parser("repro", help="re-run std & mycode on a saved case input.txt")
    p_repro.add_argument("case_dir", type=str)
    p_repro.add_argument("--tl", type=float, default=5.0)
    p_repro.add_argument("--ml", type=int, default=None)
    p_repro.add_argument("--debug", action="store_true")
    p_repro.add_argument("--chk", action="store_true")
    p_repro.add_argument("--bt", action="store_true")

    sub.add_parser("clean", help="clean build/tmp/last, reset case id, keep cases")

    p_cases = sub.add_parser("cases", help="manage history cases")
    p_cases_sub = p_cases.add_subparsers(dest="action", required=True)
    p_cases_sub.add_parser("list", help="list cases")
    p_clear = p_cases_sub.add_parser("clear", help="clear cases directory")
    p_clear.add_argument("--yes", action="store_true")
    p_retest = p_cases_sub.add_parser("retest", help="retest all cases with current code")
    p_retest.add_argument("--tl", type=float, default=5.0)
    p_retest.add_argument("--ml", type=int, default=None)
    p_retest.add_argument("--debug", action="store_true")
    p_retest.add_argument("--chk", action="store_true")
    p_retest.add_argument("--bt", action="store_true")

    args = parser.parse_args()

    if args.cmd == "clean":
        do_clean()
        return
    if args.cmd == "run":
        do_run(args.n, args.tl, args.ml, args.ml_gen, args.debug, args.chk, args.bt)
        return
    if args.cmd == "repro":
        do_repro(Path(args.case_dir), args.tl, args.ml, args.debug, args.chk, args.bt)
        return
    if args.cmd == "cases":
        if args.action == "list":
            do_cases_list()
        elif args.action == "clear":
            do_cases_clear(args.yes)
        elif args.action == "retest":
            do_cases_retest(args.tl, args.ml, args.debug, args.chk, args.bt)
        return

if __name__ == "__main__":
    main()
