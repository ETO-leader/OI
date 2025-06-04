from random import randint

n = 400

arr = [[randint(0, 998244352) for _ in range(n)] for _ in range(n - 1)]

for i in range(n - 1):
    arr[i][i] = 0

print(n)

for i in arr:
    print(*i)

q = 50000

print(q)

for i in range(q):
    print(1)
    x, y = randint(1, n - 1), randint(1, n)
    print(x, y, randint(0, 998244352))
