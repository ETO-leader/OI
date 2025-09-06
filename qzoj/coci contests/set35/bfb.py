def calc(_inf : str, _ouf : str):
    with open(_inf, 'r') as inf:
        with open(_ouf, 'w') as ouf:
            n = int(inf.readline())
            v = list(map(lambda x : int(x) - 1, inf.readline().split()))
            q = int(inf.readline())
            def getTop(x):
                nonlocal v, n
                for _ in range(n + 7):
                    if v[x] < 0:
                        return str(x + 1)
                    x = v[x]
                return 'CIKLUS'
            for _ in range(q):
                op, x = map(int, inf.readline().split())
                if op == 1:
                    ouf.write(f'{getTop(x - 1)}\n')
                else:
                    v[x - 1] = -1
            ouf.close()
        inf.close()