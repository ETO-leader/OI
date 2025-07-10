from random import randint

n = randint(1, 100)

print(n, randint(1, n))

for i in range(2, n + 1):
    print(randint(1, i - 1), i, randint(1, 1000000))

