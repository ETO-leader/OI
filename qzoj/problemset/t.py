# -*- coding: utf-8 -*-
import sys
def solve():
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data)
    N = next(it)
    rects = []
    for _ in range(N):
        x1 = next(it); y1 = next(it); x2 = next(it); y2 = next(it)
        # 输入保证 x1<=x2, y1<=y2
        rects.append((x1,y1,x2,y2))
    M = next(it)
    queries = [next(it) for _ in range(M)]
    # keep original order
    q_with_idx = [(q,i) for i,q in enumerate(queries)]
    # queries are said to be given sorted ascending, but we handle general case
    maxq = max(queries) if M>0 else 0

    # Collect global breakpoints
    breaks = {0, maxq+1}
    for (x1,y1,x2,y2) in rects:
        breaks.add(abs(x1)); breaks.add(abs(x2)); breaks.add(abs(y1)); breaks.add(abs(y2))
    G = sorted(breaks)
    # map value -> index of G (interval index is i for [G[i], G[i+1]))
    pos = {v:i for i,v in enumerate(G)}
    interval_count = len(G)-1
    A = [0]*(interval_count)  # coef for t^2
    B = [0]*(interval_count)  # coef for t
    C = [0]*(interval_count)  # coef constant

    # helper: compute (p,q) so that overlap length ax(t) = p*t + q on interval where t_sample in interval
    def linear_coef_1d(L, R, t_sample):
        # low = max(L, -t), high = min(R, t)
        # cond1: -t >= L  <=> t <= -L
        # cond2: t <= R
        cond1 = (t_sample <= -L)
        cond2 = (t_sample <= R)
        if cond1 and cond2:
            # low = -t, high = t -> 2t+1
            return 2, 1
        if cond1 and (not cond2):
            # low = -t, high = R -> t + R + 1
            return 1, R + 1
        if (not cond1) and cond2:
            # low = L, high = t -> t - L + 1
            return 1, 1 - L
        # else low=L, high=R -> const R-L+1
        return 0, R - L + 1

    # For each rectangle, build its own local criticals (subset of G) and add coefficients to corresponding global intervals
    for (x1,y1,x2,y2) in rects:
        local_points = [0, abs(x1), abs(x2), abs(y1), abs(y2), maxq+1]
        # keep unique & sorted
        local_points = sorted(set(local_points))
        for j in range(len(local_points)-1):
            s0 = local_points[j]
            s1 = local_points[j+1]
            if s0 >= s1:
                continue
            # find index in global G: interval index i such that [G[i], G[i+1]) == [s0, s1)
            i = pos[s0]
            # pick t_sample = s0 (left-closed interval)
            t_sample = s0
            px, qx = linear_coef_1d(x1, x2, t_sample)
            py, qy = linear_coef_1d(y1, y2, t_sample)
            a = px * py
            b = px * qy + py * qx
            c = qx * qy
            A[i] += a
            B[i] += b
            C[i] += c

    # answer queries: for each q, find interval index i with binary search on G
    import bisect
    res = [0]*M
    for idx, q in enumerate(queries):
        # find rightmost G[pos] <= q => pos = bisect_right(G, q)-1
        i = bisect.bisect_right(G, q) - 1
        if i < 0:
            # q < 0 not possible because q >= 0 by statement
            res[idx] = 0
        elif i >= interval_count:
            # beyond last interval (shouldn't happen because G contains maxq+1)
            i = interval_count-1
            t = q
            res[idx] = A[i]*t*t + B[i]*t + C[i]
        else:
            t = q
            res[idx] = A[i]*t*t + B[i]*t + C[i]

    # print in input order (they were given in order; we preserved)
    out = '\n'.join(str(x) for x in res)
    sys.stdout.write(out)

if __name__ == "__main__":
    solve()
