LC = 207339

def line(lc):
    print('{', end = '')
    with open('table.export', 'r') as inf:
        for i in range(lc):
            print(inf.readline().split()[0], end = ',')
    print('}')

line(LC)
