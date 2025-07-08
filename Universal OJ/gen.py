from random import shuffle

n = 100000
tid = 2

print(tid, n)

a = [i for i in range(1, n + 1)]

shuffle(a)

print(*a)

