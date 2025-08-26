from sys import stderr

N, P = map(int, input().split())

def calc(a : list):

    N = len(a)

    cnt = 0

    ua = [a[i] for i in range(N)]

    for i in range(100):
        cnt += 1
        for i in range(1, N):
            a[i] += a[i - 1]
            a[i] %= P
        if a == ua:
            break

    na = a[::-1]

    while len(na) > 0 and na[-1] == 0:
        na.pop()

    if a == ua:
        w = 1
        while w < len(na):
            w *= P
        if w != cnt:
            stderr.write(f'{a} {na}\n')
        return cnt
    else:
        stderr.write('FAIL\n')
        return 0
    
arr = []

def dfs():
    if len(arr) == N:
        return calc(arr)
    res = 0
    for i in range(P):
        arr.append(i)
        res += dfs()
        arr.pop()
    return res

print(dfs())

