from sys import argv
from random import randint

MaxN = int(argv[1])
MaxM = int(argv[2])

N = randint(1, MaxN)
M = randint(1, MaxM)

print(N, M)

Ina = [False] * (N + M + 7)
Inb = [False] * (N + M + 7)

for i in range(N):
    val = randint(1, N + M)
    while Ina[val]: val = randint(1, N + M)
    print(val, end = ' ')
    Ina[val] = True
print()
for i in range(N):
    print(randint(1, 1000000000), end = ' ')
print()
for i in range(M):
    val = randint(1, N + M)
    while Inb[val]: val = randint(1, N + M)
    print(val, end = ' ')
    Inb[val] = True
print()
for i in range(M):
    print(randint(1, 1000000000), end = ' ')
print()
