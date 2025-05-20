from random import randint

print(100)

def gen():
    n = 6
    arr = [randint(1, i + 1) for i in range(n)]
    print(n)
    for i in arr: print(i, end = ' ')
    print()

for i in range(100):
    gen()
