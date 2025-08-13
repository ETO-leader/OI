import random as rng

N = 200000
M = 1000000000

print(N)

for i in range(2, N + 1):
    print(rng.randint(1, i - 1), i)

Q = 5

print(Q, M)

for i in range(Q):
    print(1, rng.randint(100, 100))

