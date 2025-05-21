from random import randint

N = 2000000

print(N)

if randint(0, 1):
    for i in range(N // 2): print(8, end = ' ')
    for i in range(N // 2): print(randint(1, N), end = ' ')
else:
    for i in range(N): print(randint(1, N), end = ' ')
print()
