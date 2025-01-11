from random import randint

def main():

    N = 100
    Q = 100

    print(N)
    print('a' * N)
    print(Q)

    for i in range(Q):
        l = randint(1, N)
        r = randint(1, N)
        k = randint(1, 10000)
        if l > r:
            tmp = l
            l = r
            r = tmp
        print(l, r, k)

if __name__ == '__main__':
    main()
