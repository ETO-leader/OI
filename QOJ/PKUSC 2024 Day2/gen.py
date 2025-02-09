from random import randint

N = 10
Q = 10

print(N, Q)

for i in range(N):
    x = randint(0, N)
    y = randint(0, N)
    print(min(x, y), max(x, y))

for i in range(Q):
    x = randint(1, N)
    y = randint(1, N)
    print(min(x, y), max(x, y))
