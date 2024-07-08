import random as rnd

N=500000
Q=5000000

print(N,Q,rnd.randint(0,2**32-1))

print(0,end=' ')

for i in range(N-1):
    print(rnd.randint(1,i+1),end=' ')

print()

