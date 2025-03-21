from random import randint

N = 300000
Q = 300000

print(2)

print(N, Q)

for i in range(N):
    print(randint(0, 2), end = '')
print()

for i in range(N):
    print(randint(0, 2), end = '')
print()

for i in range(Q):
    xl = randint(0, N - 1)
    yl = randint(0, N - 1)
    ln = randint(1, N - max(xl, yl))
    print(xl, yl, ln)
