from random import randint

N = 20

print(1)

print(N)

for i in range(N - 1):
    print(*[randint(0, N * 2 - 1) for _ in range(N)])

for i in range(N):
    print(*[randint(0, N * 2 - 1) for _ in range(N - 1)])

