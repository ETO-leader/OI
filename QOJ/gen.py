import random

N = 100000

print(N, 0)

a = [i for i in range(N)]

random.shuffle(a)

for i in a: print(i, end = ' ')
print()
