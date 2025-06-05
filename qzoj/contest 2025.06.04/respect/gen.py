from random import randint, seed

def gentree(n, _sd):
    seed(_sd)
    for i in range(2, n + 1):
        print(i - 1, i, 1000)
    print()

n = 100000

_sd = randint(1, 1145141919810)

print(n)
gentree(n, _sd)
gentree(n, _sd)
gentree(n, _sd)
