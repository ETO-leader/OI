from bfc import calc
from random import randint

def genInput(_ouf : str, n : int, q : int):
    with open(_ouf, 'w') as ouf:
        ouf.write(f'{n} {q}\n')
        a = [randint(0, 100000) for _ in range(n)]
        for x in a:
            ouf.write(f'{x} ')
        ouf.write('\n')
        la = n
        for i in range(q):
            op = randint(1, 4)
            if op == 1 or op == 2:
                l, r, x = randint(1, la), randint(1, la), randint(1, 100)
                if l > r:
                    l, r = r, l
                ouf.write(f'{op} {l} {r} {x}\n')
            elif op == 3:
                p, w = randint(1, la + 1), randint(0, 100000)
                ouf.write(f'{op} {p} {w}\n')
            else:
                l, r = randint(1, la), randint(1, la)
                if l > r:
                    l, r = r, l
                ouf.write(f'{op} {l} {r}\n')

def genOutput(_inf : str, _ouf : str):
    calc(_inf, _ouf)

def main():
    genInput('c-inf', 3000, 3000)
    genOutput('c-inf', 'c-ans')

if __name__ == '__main__':
    main()

