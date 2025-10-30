from random import randint

es = set()

N = 6
M = 9

while(len(es) < M):
    s = []
    while len(s) < 2:
        v = randint(1, N)
        if v not in s:
            s.append(v)
    es.add((s[0], s[1]))

print(N, M, randint(N ** 3, 10 ** 18))

for u, v in es:
    print(u, v)

