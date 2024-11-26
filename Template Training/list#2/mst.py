
class dsu:

    def __init__(self, N):
        self.f = list(range(1, N + 1))#[i for i in range(N)]
    
    def findset(self, x):
        self.f[x] = (x if self.f[x] == x else self.findset(self.f[x]))
        return self.f[x]

    def merge(self, x, y):
        self.f[self.findset(x)] = self.findset(y)


def findset(x):
    pass

if __name__ == '__main__':
    read = lambda : list(map(int, input().split()))
    N, M = read()
    es = sorted([read() for i in range(M)], key = lambda x : x[2])
    
    ds = dsu(N + 1)
    # ds = list(range(1, N + 1))
    
    #es.sort(key= lambda x: x[2])
    ans = 0
    edgecnt = 0

    for u,v,w in es:
        if ds.findset(u) == ds.findset(v): continue
        ds.merge(u,v)
        ans += w
        edgecnt += 1
    
    print(ans if edgecnt == N - 1 else 'orz')

