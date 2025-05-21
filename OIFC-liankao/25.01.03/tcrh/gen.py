# N = 100000
# K = 200

# edge = []

# P = 50000

# for i in range(1, P):
#     if i + 1 < P: edge.append((i, i + 1))
#     edge.append((i, P))

# for i in range(P, N):
#     edge.append((i, i + 1))

# print(N, len(edge), K)

# for u, v in edge:
#     print(u, v)

from random import randint

N = 100000
M = 200000
K = 200

print(N, M, K)

las = 1

for i in range(2, N + 1):
    ty = randint(0, 5)
    print(randint(1, i - 1) if ty else las, i)
    if not ty: las = i

for i in range(M - N + 1):
    u = randint(1, N)
    v = randint(1, N)
    while u == v:
        u = randint(1, N)
        v = randint(1, N)
    if u > v:
        print(v, u)
    else:
        print(u, v)
