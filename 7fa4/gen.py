from random import randint, shuffle

n = 100
q = 198

print(n, q)

es = [(randint(1, i - 1), i) for i in range(2, n + 1)]

shuffle(es)

for u, v in es:
    print(f'A {u} {v}')
    print(f'Q {u}')
