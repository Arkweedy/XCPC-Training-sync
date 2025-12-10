import math
from collections import defaultdict

EPS = 1e-7

def dot(a, b): return sum(x*y for x, y in zip(a, b))
def add(a, b): return tuple(x+y for x, y in zip(a, b))
def sub(a, b): return tuple(x-y for x, y in zip(a, b))
def length(v): return math.sqrt(dot(v, v))
def normalize(v):
    l = length(v)
    return tuple(x/l for x in v)
def cross(a, b):
    return (a[1]*b[2] - a[2]*b[1],
            a[2]*b[0] - a[0]*b[2],
            a[0]*b[1] - a[1]*b[0])

def generate_perpendicular_unit_vectors(v, step_count=36):
    if abs(v[0]) < 0.9:
        other = (1, 0, 0)
    else:
        other = (0, 1, 0)
    u1 = sub(other, tuple(dot(other, v) * x for x in v))
    u1 = normalize(u1)
    u2 = cross(v, u1)
    res = []
    for i in range(step_count):
        theta = 2 * math.pi * i / step_count
        dir_vec = tuple(math.cos(theta) * u1[j] + math.sin(theta) * u2[j] for j in range(3))
        res.append(normalize(dir_vec))
    return res

def meet_in_middle(n, step_count=36):
    n1 = n // 2
    n2 = n - n1
    forward_states = defaultdict(list)
    def dfs1(k, pos, dir_vec, path):
        if k == n1:
            key = tuple(round(c, 7) for c in pos)
            forward_states[key].append((dir_vec, path[:]))
            return
        for d in generate_perpendicular_unit_vectors(dir_vec, step_count):
            new_pos = add(pos, d)
            path.append(new_pos)
            dfs1(k+1, new_pos, d, path)
            path.pop()
    start_dir = (1.0, 0.0, 0.0)
    dfs1(1, start_dir, start_dir, [(0.0, 0.0, 0.0), start_dir])
    def dfs2(k, pos, dir_vec, path):
        if k == n2:
            key = tuple(round(c, 7) for c in pos)
            if key in forward_states:
                for fd, fpath in forward_states[key]:
                    if abs(dot(fd, dir_vec)) < EPS:
                        return fpath + path[-2::-1]
            return None
        for d in generate_perpendicular_unit_vectors(dir_vec, step_count):
            new_pos = add(pos, d)
            path.append(new_pos)
            res = dfs2(k+1, new_pos, d, path)
            if res: return res
            path.pop()
        return None
    end_dir = (1.0, 0.0, 0.0)
    return dfs2(1, end_dir, end_dir, [(0.0, 0.0, 0.0), end_dir])

if __name__ == "__main__":
    step_count = 12  # 先用小步长找
    for edges in [9]:
        print(f"尝试 {edges} 条边...")
        path = meet_in_middle(edges, step_count)
        if path:
            print(f"找到 {edges} 条边方案：")
            for p in path:
                print(f"{p[0]:.7f} {p[1]:.7f} {p[2]:.7f}")
            break
    print("如需更高精度，可将 step_count 提到 36 重新运行")
