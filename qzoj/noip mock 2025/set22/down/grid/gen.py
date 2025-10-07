#!/usr/bin/env python3
"""
测试用例生成器（支持多种模式）
默认输出到 stdout，可以重定向到文件。

用法示例:
  python3 gen_tests.py --mode random --N 12 --cols 20 --max_ops 40 --seed 1 > grid.in

参数:
  --mode {random, chain, sparse, full, empty}
  --N 行数
  --cols 列数（生成区间时用的列范围 1..cols）
  --max_ops 最大操作数 M（实际 M 随机在 [0, max_ops]）
  --seed 随机种子
  --outfile 指定输出文件（若省略则打印 stdout）
"""

import random
import argparse
import sys

def gen_random(N, cols, max_ops):
    ops = []
    M = random.randint(0, max_ops)
    for _ in range(M):
        p = random.randint(1, N)
        l = random.randint(1, cols)
        # 随机长度，偏短
        r = min(cols, l + random.randint(0, max(1, cols//4)))
        ops.append((p, l, r))
    return ops

def gen_chain(N, cols):
    # 产生链式交叠，使得 row i 与 row i+1 有交点（方便构造一个无须删除的例子）
    ops = []
    # 让每行只有一个区间，且 i 与 i+1 相交
    start = 1
    for i in range(1, N+1):
        l = start + random.randint(0, 1)
        r = min(cols, l + random.randint(0, max(1, cols//6)))
        ops.append((i, l, r))
        # 保持下一个行的区间与当前有交集
        start = max(1, l - random.randint(0, 1))
    return ops

def gen_sparse(N, cols, max_ops):
    # 少量随机操作，许多空行
    ops = []
    M = random.randint(0, max_ops)
    for _ in range(M):
        p = random.randint(1, N)
        if random.random() < 0.7:
            # very short interval
            l = random.randint(1, cols)
            r = min(cols, l + random.randint(0,1))
        else:
            l = random.randint(1, cols)
            r = min(cols, l + random.randint(0, cols//3))
        ops.append((p, l, r))
    return ops

def gen_full(N, cols):
    # many operations covering wide ranges
    ops = []
    for i in range(1, N+1):
        # 每行多个区间，可能重叠
        k = random.randint(1, min(5, cols))
        for _ in range(k):
            l = random.randint(1, cols)
            r = min(cols, l + random.randint(0, max(1, cols//3)))
            ops.append((i, l, r))
    return ops

def gen_empty(N):
    return []


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--mode", choices=["random","chain","sparse","full","empty"], default="random")
    parser.add_argument("--N", type=int, default=10)
    parser.add_argument("--cols", type=int, default=20)
    parser.add_argument("--max_ops", type=int, default=50)
    parser.add_argument("--seed", type=int, default=None)
    parser.add_argument("--outfile", type=str, default=None)
    args = parser.parse_args()

    if args.seed is not None:
        random.seed(args.seed)

    if args.mode == "random":
        ops = gen_random(args.N, args.cols, args.max_ops)
    elif args.mode == "chain":
        ops = gen_chain(args.N, args.cols)
    elif args.mode == "sparse":
        ops = gen_sparse(args.N, args.cols, args.max_ops)
    elif args.mode == "full":
        ops = gen_full(args.N, args.cols)
    elif args.mode == "empty":
        ops = gen_empty(args.N)
    else:
        ops = []

    M = len(ops)
    out_lines = []
    out_lines.append(f"{args.N} {M}")
    for p,l,r in ops:
        out_lines.append(f"{p} {l} {r}")
    out = "\n".join(out_lines) + "\n"

    if args.outfile:
        with open(args.outfile, "w") as f:
            f.write(out)
        print(f"written to {args.outfile}", file=sys.stderr)
    else:
        sys.stdout.write(out)

if __name__ == "__main__":
    main()
