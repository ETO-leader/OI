import sys
import random as rnd

def generateMap(R,C):
    res = [['.' for qwq in range(C)] for tat in range(R)]
    for i in range(R):
        for j in range(C):
            res[i][j] = '......xxAB'[rnd.randint(0,9)]
    return res

rgx = int(sys.argv[1])
rgy = int(sys.argv[2])

mp=generateMap(rgx,rgy)

print(2,rgx,rgy)

for i in range(1,3):
    rx = rnd.randint(0,rgx-1)
    ry = rnd.randint(0,rgy-1)
    while mp[rx][ry].isdigit():
        rx = rnd.randint(0,rgx-1)
        ry = rnd.randint(0,rgy-1)
    mp[rx][ry] = str(i)

for i in mp:
    for j in i: print(j,end='')
    print()
