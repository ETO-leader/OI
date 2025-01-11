from sys import argv

log = open('process.log')

with open(argv[1]) as inf:
    read = lambda str : list(map(int, str.split()))
    for i in inf:
        a, b, c, d, e = read(i)
        if argv[2] == 'chg':
            print(a + 1, b + 1, c, d, e)
        else:
            print(f'{a} {b} ({c},{d},{e})')
