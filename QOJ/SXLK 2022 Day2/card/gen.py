from sys import argv
from random import randint

# Consts

SIGN = argv[1]

if SIGN == 'FULL':
    N = 10 ** 6
    V = 2000
    M = 1500
    xi = 11
elif SIGN == "CHECK":
    N = 10
    V = 300
    M = 1500
    xi = 3
else:
    N = 0
    V = 0
    M = 0
    xi = 0

# Check Prime Numbers

def isPrime(x):
    if x == 1: return False
    cur = 2
    while cur * cur < x + 1:
        if x % cur == 0: return False
        cur += 1
    return True

# Get Prime Numbers

def getPrime():
    res = []
    for i in range(2, V + 1):
        if isPrime(i): res.append(i)
    return res

def main():
    p = getPrime()
    print(N)
    for i in range(N): print(randint(1, V), end = ' ')
    print()
    print(M)
    for i in range(M):
        print(xi, end = ' ')
        for i in range(xi): print(p[randint(0, len(p) - 1)], end = ' ')
        print()

if __name__ == '__main__':
    main()
