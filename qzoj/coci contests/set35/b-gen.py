from bfb import calc
from random import randint

def genInput(_ouf : str, n : int, q : int):
    with open(_ouf, 'w') as ouf:
        ouf.write(f'{n}\n')
        vx = [randint(0, n) for _ in range(q)]
        for x in vx:
            ouf.write(f'{x} ')
        ouf.write('\n')
        vaild = []
        for i in range(n):
            if vx[i] > 0:
                vaild.append(i)
        ouf.write(f'{q}\n')
        for i in range(q):
            op = randint(1, 2 if len(vaild) > 0 else 1)
            if op == 1:
                ouf.write(f'{op} {randint(1, n)}\n')
            else:
                p = randint(0, len(vaild) - 1)
                vx[vaild[p]] = -1
                ouf.write(f'{op} {vaild[p] + 1}\n')
                del vaild[p]

def genOutput(_inf : str, _ouf : str):
    calc(_inf, _ouf)

def main():
    genInput('b-inf', 3000, 3000)
    genOutput('b-inf', 'b-ans')

if __name__ == '__main__':
    main()

