from random import randint

N = 6
V = randint(1, 100)

print(N, V)

for i in range(N):
    print(randint(1, V), end = ' ')
print()
