import random as rng

n = 50
m = 50

print(n, m)

for i in range(n):
    for j in range(m):
        print('qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890*-'[rng.randint(0, 63)], end = '')
    print()

for i in range(10000):
    print('qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890*-'[rng.randint(0, 63)], end = '')
print()

