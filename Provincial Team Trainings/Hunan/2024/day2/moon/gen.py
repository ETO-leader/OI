from random import randint

N = 15
M = 20

print(N, M)

for i in range(M):
    print(2, end = ' ')
print()

es = set()

while len(es) < M:
    x = set()
    while len(x) < 2:
        x.add(randint(1, N))
    u, v = x
    if u > v:
        t = u
        u = v
        v = t
    es.add((u, v))

for u, v in es:
    print(u, v)

