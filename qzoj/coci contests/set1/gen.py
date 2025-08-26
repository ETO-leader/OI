import random

N = 6
L = 50000
Q = 100000

print(N, Q)

for i in range(N):
    print(L, end = ' ')
    for _ in range(L): print(random.randint(1,10**4), end = ' ')
    print()

for i in range(Q):
    x = set()
    while len(x) < 2: x.add(random.randint(1, N))
    u, v = x
    print(u, v)
