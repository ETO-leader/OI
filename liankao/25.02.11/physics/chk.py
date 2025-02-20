N = 50

c = [[0] * N for _ in range(N)]

c[0][0] = 1

for i in range(1, N):
    for j in range(N):
        c[i][j] = c[i - 1][j]
        if j: c[i][j] += c[i - 1][j - 1]

# 右边比左边多 DL

for DL in range(0, 10):
    for L in range(0, 10):
        for R in range(0, 10):
            ans = 0
            for lc in range(0, L + 1):
                for rc in range(0, R + 1):
                    if lc < rc + DL:
                        ans += c[L][lc] * c[R][rc]
            print(f'delta = {DL}, L = {L}, R = {R}, ans = {ans}')
