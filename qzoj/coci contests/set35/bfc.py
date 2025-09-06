def calc(_inf : str, _ouf : str):
    with open(_inf, 'r') as inf:
        with open(_ouf, 'w') as ouf:
            n, q = map(int, inf.readline().split())
            a = list(map(int, inf.readline().split()))
            for i in range(q):
                qy = list(map(int, inf.readline().split()))
                if qy[0] == 1:
                    op, l, r, x = qy
                    l -= 1
                    r -= 1
                    for i in range(l, r + 1):
                        a[i] = x
                elif qy[0] == 2:
                    op, l, r, x = qy
                    l -= 1
                    r -= 1
                    w = 0
                    for i in range(l, r + 1):
                        w += x
                        a[i] += w
                elif qy[0] == 3:
                    op, c, x = qy
                    c -= 1
                    a = a[:c] + [x] + a[c:]
                else:
                    op, l, r = qy
                    l -= 1
                    r -= 1
                    ouf.write(f'{sum(a[l:r + 1])}\n')
            ouf.close()
        inf.close()

if __name__ == '__main__':
    calc('inf', 'ouf')
