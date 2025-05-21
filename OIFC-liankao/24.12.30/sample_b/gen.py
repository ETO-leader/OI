from random import randint

def main():

    N = 1000
    T = 3

    print(N, T)

    las = 1

    def upd(cur):
        nonlocal las
        res = las
        las = cur
        return res

    for i in range(2, N + 1):
        print(randint(1, randint(1, 11) if not randint(0, 30) and i > 11 else (randint(1, i - 1) if randint(0, 5) else upd(i))), i)

if __name__ == '__main__':
    main()
