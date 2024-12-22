from sys import argv
from random import randint


def main():
    n = int(argv[1])
    print(n)
    for i in range(n):
        print(randint(-1000,1000),randint(0,0),randint(1,50))

if __name__ == '__main__':
    main()

