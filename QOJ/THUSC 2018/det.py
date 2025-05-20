import numpy as np
import random as rng

x = 187473

def matrix():
    a = [[0] * 10 for _ in range(10)]
    for i in range(10):
        for j in range(10):
            a[i][j] = rng.randint(0, 1)
    for i in range(10):
        a[i][i] = 1
    return a

def makeMatrix(x):
    a = matrix()
    while int(round(np.linalg.det(a))) != x:
        a = matrix()
    return a

def printMatrix(x):
    for a in x:
        for i in a:
            print(i, end = ' ')
        print()
for i in range(2, x + 1):
    while x % i == 0:
        printMatrix(makeMatrix(i))
        print()
        x //= i
