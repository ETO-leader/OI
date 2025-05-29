from random import randint

N = 400000
Q = 400000
V = 1000000000
dV = 1000000

print(N, Q)

for i in range(N):
    print(randint(-V, V), end = ' ')
print()

def genpair():
    x = randint(1, N)
    y = randint(1, N)
    return (min(x, y), max(x, y))

for i in range(Q):
    op = randint(0, 1)
    if op == 1:
        l, r = genpair()
        print(1, l, r, randint(1, dV))
    else:
        l, r = genpair()
        print(2, l, r)
