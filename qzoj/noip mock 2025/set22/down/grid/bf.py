#!/usr/bin/env python3
"""
暴力解（对拍用）
读取格式（stdin 或 文件重定向）:
N M
p1 l1 r1
...
pM lM rM

输出:
第一行 k （最少删除的行数）
第二行 列表（k 个被删除的行号，任意顺序；k=0 时输出空行）

说明:
- 对每一行，我们先把所有区间合并为不相交的区间列表。
- 定义行 i 与行 j 相交 iff 存在一个列 x 同时在两行的黑区间中（即两区间集合有交集）。
- 转化为有向无环图（i < j 且相交就有边 i->j），求最长路径（最长递增序列），用 O(N^2) DP。
- 返回保留序列，输出需删除的行索引集合。
"""

import sys

def merge_intervals(intervals):
    if not intervals:
        return []
    intervals.sort()
    res = []
    cur_l, cur_r = intervals[0]
    for l, r in intervals[1:]:
        if l <= cur_r + 1:
            cur_r = max(cur_r, r)
        else:
            res.append((cur_l, cur_r))
            cur_l, cur_r = l, r
    res.append((cur_l, cur_r))
    return res

def intersects(a, b):
    # a, b are lists of disjoint sorted intervals
    i = j = 0
    while i < len(a) and j < len(b):
        l1, r1 = a[i]
        l2, r2 = b[j]
        if r1 < l2:
            i += 1
        elif r2 < l1:
            j += 1
        else:
            return True
    return False

def solve(N, ops):
    # ops: list of (p, l, r)
    rows = [[] for _ in range(N+1)]  # 1-indexed
    for p, l, r in ops:
        rows[p].append((l, r))
    for i in range(1, N+1):
        rows[i] = merge_intervals(rows[i])

    # DP longest path in DAG: dp[i] = length of longest path ending at i
    dp = [0] * (N+1)
    prev = [-1] * (N+1)
    best_len = 0
    best_end = 1
    for j in range(1, N+1):
        dp[j] = 1
        prev[j] = -1
        for i in range(1, j):
            if dp[i] + 1 > dp[j]:
                # if rows i and j intersect
                if intersects(rows[i], rows[j]):
                    dp[j] = dp[i] + 1
                    prev[j] = i
        if dp[j] > best_len:
            best_len = dp[j]
            best_end = j

    # reconstruct kept sequence
    kept = []
    cur = best_end
    while cur != -1:
        kept.append(cur)
        cur = prev[cur]
    kept.reverse()
    kept_set = set(kept)
    deleted = [i for i in range(1, N+1) if i not in kept_set]
    return deleted

def read_input_from_stdin():
    data = sys.stdin.read().strip().split()
    if not data:
        return 0, []
    it = iter(data)
    N = int(next(it))
    M = int(next(it))
    ops = []
    for _ in range(M):
        p = int(next(it)); l = int(next(it)); r = int(next(it))
        ops.append((p, l, r))
    return N, ops

if __name__ == "__main__":
    N, ops = read_input_from_stdin()
    deleted = solve(N, ops)
    print(len(deleted))
    if len(deleted) > 0:
        print(" ".join(map(str, deleted)))
    else:
        print()
