import random as rnd

n = 100000

k = rnd.randint(1, 10)

print(n, k)

arr = list(range(1, n + 1))

rnd.shuffle(arr)

for i in range(k): print(arr[i], end = ' ')
print()

for i in range(2, n + 1):
    print(rnd.randint(1, i - 1), i)
print()

# n = 999999
# ad = 499999
# print(n, ad)

# for i in range(ad + 1, n + 1): print(i, end = ' ')

# for i in range(2, ad + 2): print(1, i)
# for i in range(2, ad + 2): print(i, i + ad)

