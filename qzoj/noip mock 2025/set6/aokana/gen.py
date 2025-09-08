from sys import argv
from random import randint

def genInput(_path : str, N : int, Q : int, V : int):
    with open(_path, 'w') as ouf:
        ouf.write(f'{N} {Q}\n')
        for i in range(N):
            l, r = randint(1, V), randint(1, V)
            if l > r:
                l, r = r, l
            w = randint(1, V)
            ouf.write(f'{l} {r} {w}\n')
        for i in range(Q):
            ouf.write(f'{randint(1, V)} ')
        ouf.write('\n')
        ouf.close()


def main():
    N, Q, V = list(map(int, argv[1:]))[:3]
    genInput('aokana.in', N, Q, V)

if __name__ == '__main__':
    main()

