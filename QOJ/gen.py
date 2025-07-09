import random as rng

__seed = rng.randint(11, 25119711)

print(__seed)

n = rng.randint(10 ** 5, 10 ** 5)

print(n)

for i in range(3, n + 1):
    print((i // 4) * 2 + (i % 2), i)

print(1, 2)

print(rng.randint(1, n), rng.randint(1, n))

