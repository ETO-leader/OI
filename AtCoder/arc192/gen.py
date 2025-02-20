from random import randint,shuffle

N = 5000

a = [i for i in range(1, N + 1)]

shuffle(a)

if a[0] > a[1]:
    x = a[1]
    a[1] = a[0]
    a[0] = x

print(N)

for i in a: print(i, end = ' ')
print()

for i in range(N + 1): print(randint(1,100000000), end = ' ')
print()
