from random import randint

N = 2 * (10 ** 5)

print(N, '\n', *[randint(1, 10 ** 3) for _ in range(N)])
