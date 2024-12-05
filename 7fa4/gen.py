from random import randint

n = 100000

print(n, 1)

for i in range(n): print(randint(1, 100000), end=' ')

for i in range(2, n + 1): print(i - 1, i)

print(1, 1)
