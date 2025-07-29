from random import randint

N = randint(1, 5)
M = randint(1, 5)
K = randint(0, N * M)

print(N, M, K)

for i in range(K):
    print(randint(1, N), randint(1, M), randint(0, 1))
