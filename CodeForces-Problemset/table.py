import os, sys

A = 1

while A < 10 ** 10:
    os.system(f'./table {A} {A + 2 * 10 ** 6} >> table.qwq')
    A += 2 * 10 ** 6
    sys.stderr.write(f'{A}\n')
