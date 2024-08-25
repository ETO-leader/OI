import random as rnd

N=5000
Q=5000

print(1)

print(N,Q)

for i in range(N):
    print("AB"[rnd.randint(0,1)],end='')
print()

for i in range(N):
    print(rnd.randint(1000000000,1000000000),end=' ')
print()

for i in range(Q):
    tp=rnd.randint(1,2)
    if tp==1:
        print(1,rnd.randint(1,N),rnd.randint(1000000000,1000000000))
    else:
        l=rnd.randint(1,N)
        r=rnd.randint(1,N)
        print(2,l,r)

