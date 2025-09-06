from random import randint

N = randint(1, 10)
V = 10
l = randint(1, N)
k = randint(1, l)

print(1)

print(N, l, k)

print(*[randint(1, V) for _ in range(N)])


