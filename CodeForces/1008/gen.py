from random import randint

n = 200000

print(1)
print(n)

for i in range(n):
    print(n * 100 - i * 100 + randint(1, 100), end=' ')
