import random as rnd

N=1000

print(N,N)

arr=[['.#'[rnd.randint(0,1)] for _ in range(N)] for __ in range(N)]

arr[0][0]='.'
arr[N-1][N-1]='.'

for x in arr:
    for y in x: print(y,end='')
    print()
