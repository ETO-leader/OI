from random import randint

A = randint(0, 10)
B = randint(0, 10)
C = randint(1, 20)
N = 3000
K = 10

print(N, K, A, B, C)

print(*[randint(1, 10000) for i in range(N)])
