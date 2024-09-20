import random as rnd

N=5

print(N)

arr=[rnd.randint(0,7) for i in range(N)]

for i in arr:
    print(i,end=' ')
print()
