from random import randint

N = randint(40, 40)
M = randint(60, 60)

def minmax(a, b):
    return (min(a, b), max(a, b))

def genedge():
    a = set()
    while len(a) < 2:
        a.add(randint(1, N))
    u, v = a
    return minmax(u, v)

def main():
    print(N, M)
    e = set()
    for i in range(2, N + 1):
        e.add((randint(1, i - 1), i))
    while len(e) < M:
        e.add(genedge())
    for u, v in e:
        print(u, v)

if __name__ == '__main__':
    main()
