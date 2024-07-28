import random as rnd

N=500000
Q=500000

print(N,Q)

for i in range(N):
    print(114514,end=' ')
print()

for i in range(Q):
    l=rnd.randint(1,N)
    r=rnd.randint(1,N)
    if l>r:
        tmp=l
        l=r
        r=tmp
    print(l,r)
