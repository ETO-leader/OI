inf = open('delete.in','r')
ouf = open('delete.out','w')

T = int(inf.readline())

for i in range(T):
    n = int(inf.readline())
    ans = 0
    for i in map(int,inf.readline().split()): ans ^= (i > 1) + 1
    ouf.write('{}\n'.format(['No','Yes'][bool(ans)]))
