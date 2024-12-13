from random import randint

n = 8
q = 10

print(n)

las = 1

for i in range(2, n + 1):
    if randint(0, 1):
        print(las, i)
        las = i
    else:
        print(randint(1, i - 1), i)

for i in range(n): print(randint(0, 1), end = ' ')
print()
for i in range(n): print(randint(-1000000000, 1000000000), end = ' ')
print()

print(q)

for i in range(q):
    if randint(0, 3): print(randint(0, 1), randint(1, n))
    else: print(2,randint(1, n), randint(-1000000000,1000000000))