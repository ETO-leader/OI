from sys import stdin, stdout
from collections import deque
from decimal import Decimal, getcontext

getcontext().prec = 300

f = dict()
lf = []
rf = []
inc = []
ch = [[]]

topord = []
cnt = 0

def gentop(n : int):
    global ch, inc, cnt, topord
    q = deque()
    for i in range(n):
        if inc[i] == 0:
            q.append(i)
    while len(q) > 0:
        u = q[0]
        q.popleft()
        topord[u] = cnt
        cnt += 1
        for v in ch[u]:
            inc[v] -= 1
            if inc[v] == 0:
                q.append(v)

def calc(u : int, v : int) -> Decimal:
    global f, lf, rf
    if (u, v) in f:
        return f[(u, v)]
    if u == v:
        f[(u, v)] = Decimal(1.0)
        return Decimal(1.0)
    res = Decimal(0.0)
    if lf[u] == -1 and rf[u] == -1 and lf[v] == -1 and rf[v] == -1:
        return Decimal(0.0)
    if lf[u] == -1 and rf[u] == -1:
        res += (calc(u, lf[v]) + calc(u, rf[v])) / 2
    elif lf[v] == -1 and rf[v] == -1:
        res += (calc(lf[u], v) + calc(rf[u], v)) / 2
    elif topord[u] < topord[v]:
        res += (calc(u, lf[v]) + calc(u, rf[v])) / 2
    else:
        res += (calc(lf[u], v) + calc(rf[u], v)) / 2
    f[(u, v)] = res
    return res

def main():
    global lf, rf, topord, inc, ch, cnt
    n, k = map(int, stdin.readline().split())
    lf = [-1] * n
    rf = [-1] * n
    topord = [-1] * n
    inc = [0] * n
    ch = [[] for _ in range(n)]
    for i in range(k):
        u, l, r = map(lambda x: int(x) - 1, stdin.readline().split())
        lf[u] = l
        rf[u] = r
        ch[l].append(u)
        ch[r].append(u)
        inc[u] += 2
    gentop(n)
    q = int(stdin.readline())
    for i in range(q):
        u, v = map(lambda x: int(x) - 1, stdin.readline().split())
        v = format(calc(u, v) * 100, 'f')
        if '.' in v:
            v = v.rstrip('0').rstrip('.')
        if v == '':
            v = '0'
        stdout.write(f'{v + "%"}\n')

if __name__ == '__main__':
    main()
