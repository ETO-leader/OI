from random import randint

N = 250000
Q = 0

print(N, Q)

for i in range(N):
    print(randint(0, 9), end = '')

for i in range(Q):
    l, r = randint(1, N), randint(1, N)
    if l > r: l, r = r, l
    print(l, r)


