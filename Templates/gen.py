import random as rng

N = 200
K = 3
Q = 100

print(1)

print(N, K, Q)

a = [i for i in range(1, N+1)]

for i in range(K):
    rng.shuffle(a)
    print(*a)

for i in range(Q):
    c = rng.randint(0, K - 1)
    l = rng.randint(0, N - 1)
    r = rng.randint(l, N - 1)
    if l > r:
        l, r = r, l
    print(c, l, r)
