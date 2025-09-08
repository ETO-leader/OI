from random import randint

T = 500000

print(T, 998244353)

for i in range(T):
    print(randint(10 ** 17, 10 ** 18), randint(1, 10 ** 18))


