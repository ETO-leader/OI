import random as rng

T = 1
n = 1024

print(T)
print(n)

for i in range(n):
    print(rng.randint(0, 1), end = ' ')
print()

arr = [0] * 16

for i in range(15):
    arr.append(1)

rng.shuffle(arr)

for x in arr:
    print(x, end = ' ')
print()
