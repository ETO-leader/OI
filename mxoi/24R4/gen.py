import random as rnd

N=13

w=[[_ for _ in range(N)] for qwq in range(N)]
c=[[_ for _ in range(N)] for qwq in range(N)]

for i in range(N):
    for j in range(N):
        w[i][j]=rnd.randint(1,1000000)
for i in range(N):
    for j in range(N):
        c[i][j]=rnd.randint(1,1000000)

arr=[_ for _ in range(N)]

rnd.shuffle(arr)

cst=0
m=0

for i in range(1,N):
    cst+=w[arr[i-1]][arr[i]]
    m+=c[arr[i-1]][i]

print(N,m)

for x in w:
    for y in x:
        print(y,end=' ')
    print()

for x in c:
    for y in x:
        print(y,end=' ')
    print()

print(cst)
