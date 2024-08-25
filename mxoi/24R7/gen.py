import random as rnd

N=5000

print(N)

for i in range(2,N+1):
    print(rnd.randint(1,i-1),i)

qa=[i for i in range(1,N+1)]
rnd.shuffle(qa)

for i in range(N-1):
    print(qa[i],end=' ')
print()
