def sign(x : int):
    return -1 if x < 0 else x > 0

def info(a : list, b : list):
    c = [min(a[i], b[i]) for i in range(3)]
    return (
        sign(a[0] - b[0]),
        sign(a[1] - b[1]),
        sign(a[2] - b[2]),
        sign(c[0] - c[1]),
        sign(c[1] - c[2]),
        sign(c[2] - c[0]),
        sign(c[0] - c[1] - c[2]),
        sign(c[1] - c[0] - c[2]),
        sign(c[2] - c[0] - c[1]),
        c[0] & 1,
        c[1] & 1,
        c[2] & 1,
        a[0] == 0,
        a[1] == 0,
        a[2] == 0,
        b[0] == 0,
        b[1] == 0,
        b[2] == 0
    )

vis = dict()

def dfs(uR, uG, uB, vR, vG, vB):
    global vis
    if min(uR, uG, uB) < 0:
        return False
    if max(vR, vG, vB) == 0:
        return False
    if max(uR, uG, uB) == 0:
        return True
    if (uR, uG, uB, vR, vG, vB) in vis:
        return vis[(uR, uG, uB, vR, vG, vB)]
    res = False
    if uR > 0:
        res |= dfs(uR - 1, uG, uB, vR, vG, vB) and (not dfs(vR - 1, vG, vB, uR - 1, uG, uB))
    if uG > 0:
        res |= dfs(uR, uG - 1, uB, vR, vG, vB) and (not dfs(vR, vG - 1, vB, uR, uG - 1, uB))
    if uB > 0:
        res |= dfs(uR, uG, uB - 1, vR, vG, vB) and (not dfs(vR, vG, vB - 1, uR, uG, uB - 1))
    vis[(uR, uG, uB, vR, vG, vB)] = res
    return res

def main():
    T = int(input())
    uinfo = dict()
    for uRx in range(11):
        for uGx in range(11):
            for uBx in range(11):
                for vRx in range(11):
                    for vGx in range(11):
                        for vBx in range(11):
                            uinfo[info([uRx, uGx, uBx], [vRx, vGx, vBx])] = (uRx, uGx, uBx, vRx, vGx, vBx)
    for i in range(T):
        uR, uG, uB, vR, vG, vB = map(int, input().split())
        S = info([uR, uG, uB], [vR, vG, vB])
        def calc():
            nonlocal S
            uRx, uGx, uBx, vRx, vGx, vBx = uinfo[S]
            return dfs(uRx, uGx, uBx, vRx, vGx, vBx)
        ans = calc()
        print('Takahashi' if ans else 'Aoki')

if __name__ == '__main__':
    main()
