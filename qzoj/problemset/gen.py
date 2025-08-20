import random as rng

N = 1000
M = 3000

print(N, M)

for i in range(N):
    for j in range(M):
        print(rng.randint(0, 1), end = '')
    print()
