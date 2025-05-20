import os

def interactx(x):
    ouf = open('inf', 'w')
    ouf.write('Type 107\n')
    ouf.write(f'{x} 0')
    ouf.close()
    
    os.system('./ai < inf > ouf')

    inf = open('ouf', 'r')
    inf.readline()
    inf.readline()
    inf.readline()
    info = inf.readline()
    print(info)
    return float(info.split()[-1])

def interacty(y):
    ouf = open('inf', 'w')
    ouf.write('Type 107\n')
    ouf.write(f'0 {y}')
    ouf.close()
    
    os.system('./ai < inf > ouf')

    inf = open('ouf', 'r')
    inf.readline()
    inf.readline()
    inf.readline()
    info = inf.readline()
    return float(info.split()[-1])

def main():
    l = -20.0
    r = 20.0
    for i in range(100):
        lmid = l + (r - l) / 3
        rmid = l + (r - l) / 3 * 2
        lw = interactx(lmid)
        rw = interactx(rmid)
        if lw > rw: l = lmid
        else: r = rmid
        print(l, r, lw, rw)
    print((l + r) / 2)

if __name__ == '__main__':
    main()
