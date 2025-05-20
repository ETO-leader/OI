import os
import random

def interact(x, y):
    ouf = open('inf', 'w')
    ouf.write('Type 107\n')
    ouf.write(f'{x} {y}')
    ouf.close()
    
    os.system('./ai < inf > ouf')

    inf = open('ouf', 'r')
    inf.readline()
    inf.readline()
    inf.readline()
    info = inf.readline()
    print(info)
    return info.split()[-1]

def main():
    x = 9.30
    y = 4.60
    cur = interact(x, y)
    while True:
        nx = x + random.uniform(-0.005,0.005)
        ny = y + random.uniform(-0.005,0.005)
        u = interact(nx, ny)
        if u == '3.': break
        if u < cur:
            cur = u
            x = nx
            y = ny
        print(x, y, cur)
    print(x, y)

if __name__ == '__main__':
    main()
