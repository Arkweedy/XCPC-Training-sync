1. vector越界无法检测，只会WA
2. test 显示： 1~100 per1， 100~1000 per10, 1000+ per100， AC/WA等信息可以分对应颜色显示
3. .stress目录设计：
    1. 专门放一个lastcases, 保留当次运行信息, 方便快速查看刚刚运行的
    2. 保留历史对拍的错误样例，可以使用对应的命令一键重测/清空
    3. 更改cases子目录结构，把meta.json和report.txt塞到子目录里面
    4. cases的子目录命名，去掉前面的FAIL_000001这样的前缀， 不过可以有一个编号，每次clean后重新开始编号
4. 测试了AC,WA,TLE,RE,MLE ，其中MLE出现问题：把MLE的限制开得很小时， GEN出现了RE报错，log如下：
arkweedy@Arkweedy-Desktop:/mnt/d/XCPC_Training/Tools/stress$ python3 stress.py run --ml 5
compiled OK. mode=release, tl=2.0s, ml=5MB
running up to 10000 rounds, stop on first non-AC...
[1] GEN RE  (saved: .stress/cases/FAIL_000001_GEN_RE_20260214_163302)
GEN RE
gen: rc=127, sig=None, 10ms
stderr (tail):
.stress/build/gen: error while loading shared libraries: libm.so.6: failed to map segment from shared object


repro: python3 stress.py repro .stress/cases/FAIL_000001_GEN_RE_20260214_163302