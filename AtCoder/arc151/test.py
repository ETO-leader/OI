
N = 20

sg = [[[-1] * 3 for _ in range(3)] for _ in range(N + 1)]

def MEX(a : list):
    x = set(a)
    for i in range(len(a) + 7):
        if not i in x: return i
    return -1

def SG(len, L, R):
    global sg
    if sg[len][L][R] != -1:
        return sg[len][L][R]
    a = []
    for i in range(len):
        if (L != 0 or i > 0) and (R != 0 or i + 1 < len):
            a.append(SG(i, L, 0) ^ SG(len - i - 1, 0, R))
        if (L != 1 or i > 0) and (R != 1 or i + 1 < len):
            a.append(SG(i, L, 1) ^ SG(len - i - 1, 1, R))
    sg[len][L][R] = MEX(a)
    return sg[len][L][R]

for i in range(N + 1):
    print(SG(i, 0, 0), SG(i, 0, 1), SG(i, 1, 0), SG(i, 1, 1), SG(i, 2, 0), SG(i, 2, 1), SG(i, 0, 2), SG(i, 1, 2), SG(i, 2, 2))
