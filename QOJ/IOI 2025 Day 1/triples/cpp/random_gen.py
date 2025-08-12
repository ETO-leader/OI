import ctypes
import random as rng
from sys import argv, stderr
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

def main():
    N = int(argv[1])
    K = int(argv[2])
    L = int(argv[3])
    
    mx = 0
    ans = []

    while True:
        pos = [i for i in range(N+1)][::2]
        rng.shuffle(pos)
        if len(pos) > L: pos = pos[:L-1]
        arr = [0] * N
    
        def add(a, b):
            nonlocal arr
            x = abs(a + b) // 2
            y = abs(a - b) // 2
            if arr[x] == 0: arr[x] = y

        for i in range(len(pos)):
            for j in range(i):
                add(pos[i], pos[j])
        
        for i in range(N):
            if arr[i] == 0:
                arr[i] = 1
        
        c = count(arr)

        stderr.write(f'current: {c}\n')

        if c > mx:
            mx = c
            ans = arr

        if mx > K - 1:
            break

    print(*ans)

if __name__ == '__main__':
    main()
