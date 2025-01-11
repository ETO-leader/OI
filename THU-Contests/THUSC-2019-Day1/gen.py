from random import randint

N = 6
Q = 20

print(N, Q)

for i in range(N):
    print(randint(1, 10), randint(1, 10))

for i in range(Q):
    op = randint(1, 3)
    l = randint(1, N)
    r = randint(1, N)
    if l > r:
        tmp = l
        l = r
        r = tmp
    if op == 1:
        print(1, l, r, randint(1, 5))
    elif op == 2:
        print(2, l, r)
    else:
        print(3, randint(1, N), randint(1,5), randint(1, 5))
