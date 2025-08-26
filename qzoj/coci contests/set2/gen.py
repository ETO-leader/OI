from random import randint

N = 8
V = 1000000
R = randint(1, N)

print(N, N)

for i in range(N):
    for j in range(N):
        print(randint(-V, V), end = ' ')
    print()

