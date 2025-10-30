from random import randint

N = 3
L = 5

print(N)

for i in range(N):
    l = randint(1, L)
    for c in range(l):
        print('ABCD'[randint(0, 3)], end = '')
    print()
