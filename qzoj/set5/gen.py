from random import randint

l = 1000000
n = 100000
k = 2

print(n, k, l)

pos = set()

while len(pos) < n:
    pos.add(randint(1, n))

for x in pos:
    print(x, randint(0, k - 1), 'LR'[randint(0, 1)])


