from random import randint, shuffle

N = 5000

print(1)

print(N)

p = list(range(N))

shuffle(p)

for i in range(N):
    print(p[i] if randint(0, 1) else -1, end = ' ')
print()
