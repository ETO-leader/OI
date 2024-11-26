import sys
from collections import deque

def main():
    read = lambda : list(map(int,input().split()))
    N,M = read()
    cost = [0] + read()
    es = [read() for _ in range(M)]
    gr = [[] for _ in range(N + 1)]
    for u, v in es: gr[u].append(v)
    dfn = [0] * (N + 1)
    low = [0] * (N + 1)
    scc = [0] * (N + 1)
    sum = [0] * (N + 1)
    ins = [False] * (N + 1)
    stc = deque()

    cnt = 0
    scccnt = 0

    def tarjan(u):
        nonlocal cnt, scccnt
        cnt += 1
        dfn[u] = low[u] = cnt
        ins[u] = True
        stc.append(u)
        for v in gr[u]:
            # sys.stderr.write(f'edge: {u} -> {v}\n');
            if not dfn[v]:
                tarjan(v)
                low[u] = min(low[u], low[v])
            elif ins[v]:
                low[u] = min(low[u], dfn[v])
        if dfn[u] == low[u]:
            cur = -1
            scccnt += 1
            while cur != u:
                cur = stc[-1]
                stc.pop()
                scc[cur] = scccnt
                sum[scccnt] += cost[cur]
                ins[cur] = False
    
    for i in range(1, N + 1):
        if not bool(dfn[i]):
            tarjan(i)

    dag = [[] for _ in range(N + 1)]
    f = [0] * (N + 1)
    vis = [False] * (N + 1)

    for u, v in es:
        if scc[u] != scc[v]:
            dag[scc[u]].append(scc[v])

    def dfs(u):
        if vis[u]: return f[u]
        vis[u] = True
        f[u] = sum[u]
        for v in dag[u]: f[u] = max(f[u], dfs(v) + sum[u])
        return f[u]

    print(max(dfs(i) for i in range(1, N + 1)))

if __name__ == '__main__':
    sys.setrecursionlimit(1000000)
    main()
