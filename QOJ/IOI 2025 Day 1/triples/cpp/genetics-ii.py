import ctypes
from random import randint, random
from sys import stderr
from ctypes import c_int, c_size_t, c_longlong, POINTER
from functools import cmp_to_key
from copy import deepcopy

lib = ctypes.CDLL('./export-triples-base.so')
lib.count.argtypes = (POINTER(c_int), c_size_t)
lib.count.restype = c_longlong

def count(a : list):
    n = len(a)
    CArrType = c_int * n
    c_a = CArrType(*a)
    return lib.count(c_a, n)

n = 500
V = 12

class Elements:
    def __init__(self, a : list):
        self.arr = deepcopy(a)
        self.val = count(a)

    def mutation(self, p : float):
        res = []
        x = randint(0, n - 1)
        for i in range(1, int(V * 1.3)):
            if(self.arr[x] != i):
                narr = list(deepcopy(self.arr))
                narr[x] = i
                chk = Elements(narr)
                if chk.val > self.val:
                    res.append(chk)
                elif random() < p ** (self.val - chk.val + 1):
                    res.append(chk)
        return res

def randomElement():
    arr = [randint(1, V) for _ in range(n)]
    return Elements(arr)

cur = [randomElement() for _ in range(200)]

cur = sorted(cur, key = lambda a: -a.val)

ans = cur[0]

while True:
    while len(cur) < 1600:
        u = randint(0, len(cur) - 1)
        c = cur[u].mutation(0.4)
        for x in c: cur.append(x)
    
    ncur = sorted(cur, key = lambda a: -a.val)
    if ans.val < ncur[0].val: ans = ncur[0]
    cur = []
    for i in range(140): cur.append(ncur[i])
    for i in range(60): cur.append(randomElement())
    stderr.write(f'{ans.val}\n')
    with open('./output_8-01-ii.txt', 'w') as ouf:
        ouf.write(f'{ans.val}\n{ans.arr}\n')
        ouf.close()



