from random import randint

N = 3000
M = 5000

print(N, M)

e = set()

def minmax(a, b):
    return (min(a, b), max(a, b))

for i in range(M):
    u, v = randint(1, N), randint(1, N)
    while u == v or minmax(u, v) in e:
        u, v = randint(1, N), randint(1, N)
    e.add(minmax(u, v))
    print(u, v)

