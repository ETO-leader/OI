from random import shuffle

N = 500
K = 10

print(N, K)

arr = [(i + 1) % (N * K) + 1 for i in range(N * K)]

# shuffle(arr)

print(*arr)
