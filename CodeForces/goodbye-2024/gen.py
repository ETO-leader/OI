import random as rnd

N = 30
M = 60
K = 300

print(1)
print(N, M)

for i in range(N):
    for j in range(M):
        print(rnd.randint(1, K) if rnd.randint(0, 1) else -1, end = ' ')
    print()
